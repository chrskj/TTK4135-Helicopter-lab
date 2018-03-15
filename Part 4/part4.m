clc; clear; %close all;

run ('init.m')
load('scope_data.mat')
load('pitch_data.mat')

global N alpha beta lambda_t mx


% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
alpha = 0.2;
beta = 20;
lambda_t = 2*pi/3;

A1 = [1 delta_t 0 0 0 0;
      0 1 -delta_t*K_2 0 0 0;
      0 0 1 delta_t 0 0; 
      0 0 -K_1*K_pp*delta_t 1-K_1*K_pd*delta_t 0 0;
      0 0 0 0 1 delta_t;
      0 0 0 0 -delta_t*K_3*K_ep 1-delta_t*K_3*K_ed];
B1 = [0 0; 
      0 0; 
      0 0; 
      K_1*K_pp*delta_t 0;
      0 0;
      0 delta_t*K_3*K_ep];

  

% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                               % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x5_0 = 0;                               % e
x6_0 = 0;                               % e_dot
x0 = [x1_0 x2_0 x3_0 x4_0 x6_0 x6_0]';           % Initial values

% Time horizon and initialization
N  = 100;                                  % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = [-(30*pi)/180 -(30*pi)/180]';                   % Lower bound on control
uu 	    = [(30*pi)/180 (30*pi)/180]';                   % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul(1);                           % Lower bound on state x3
xu(3)   = uu(1);                          % Upper bound on state x3
xl(5) = ul(2);
xu(5) = uu(2);

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N,M,xl,xu,ul,uu); % hint: gen_constraints
%vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
%vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

%% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
% Travel, pitch, elevation
Q1 = diag([10 0 0 0 0 0]);              % Weight on state x
% pitch ref, elev ref
R1 = diag([1 1]);
Q = gen_q(Q1,R1,N,M);                                  % Generate Q, hint: gen_q
c = zeros(N*mx+M*mu,1);                                  % Generate c, this is the linear constant term in the QP

% Generate function to be minimized
phi = @(z) 0.5 * z' * Q * z;



%% Generate system matrixes for linear model
Aeq = gen_aeq(A1,B1,N,mx,mu);             % Generate A, hint: gen_aeq
beq = zeros(size(Aeq, 1), 1);             % Generate b
beq(1:mx) = A1*x0;

%% Solve QP problem with linear model
tic
options = optimoptions('fmincon', 'Algorithm', 'sqp');
[z,lambda] = fmincon(phi, z0, [], [], Aeq, beq, vlb, vub, @nonlin_con, options);
t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+Q(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states


num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u1 = [z(N*mx+1:mu:N*mx+M*mu); z(N*mx+M*mu)]; % Control input from solution
u2 = [z(N*mx+2:mu:N*mx+M*mu); z(N*mx+M*mu)];

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution
x5 = [x0(5);z(5:mx:N*mx)];              % State x5 from solution
x6 = [x0(6);z(6:mx:N*mx)];              % State x6 from solution


x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];
u1  = [zero_padding; u1; zero_padding];
u2  = [zero_padding; u2; zero_padding];

u_opt   = [u1 u2];
x_opt = [x1 x2 x3 x4 x5 x6];


t = 0:delta_t:delta_t*(length(u_opt)-1);

constraint = [zero_padding; 0; alpha* exp(-beta*(z(1:mx:N*mx)-lambda_t).^2); zero_padding];


%% LQR things

% travel, pitch, elevation
Q_LQR = diag([10 1 1 1 1 1]);              % Weight on state x
R_LQR = diag([1 1]);

[K,S,e] = dlqr(A1, B1, Q_LQR, R_LQR);

