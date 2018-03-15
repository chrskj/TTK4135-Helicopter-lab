close all; clc;

global lambda_t mx alpha beta N 

load('elev_data.mat');
load('pitch_data.mat');
load('scope_data.mat');

figure(1)
% Travel
subplot(3,1,1)
hold on;
grid on;
plot(scope_data(1,:), scope_data(2,:)*(180/pi))
plot(t, (x1*(180/pi)), 'r')
legend('Travel','Optimal travel')
ylabel('Angle [deg]')
xlim([0 25])
% Pitch
subplot(3,1,2)
hold on;
grid on;
plot(scope_data(1,:), scope_data(4,:)*(180/pi))
plot(t, x3*(180/pi), 'r')
legend('Pitch', 'Optimal pitch')
ylabel('Angle [deg]')
xlim([0 25])
% Elevation
subplot(3,1,3)
hold on;
grid on;
plot(scope_data(1,:), scope_data(6,:)*(180/pi))
plot(t, x5*(180/pi), 'r')
plot(t, constraint*(180/pi), 'm', 'LineWidth', 1)
legend('Elevation', 'Optimal Elevation', 'Constraint')
ylabel('Angle [deg]')
xlabel('Time [s]')
xlim([0 25])

figure(2)
subplot(2,1,1); 
hold on
grid on
plot(elev_data(1,:), elev_data(2,:)*(180/pi), 'LineWidth', 1)
plot(t, u2*(180/pi), 'r', 'LineWidth', 1)
plot(t, constraint*(180/pi), 'm', 'LineWidth', 1)
ylabel('Angle [rad]')
legend('Elev ref', 'Optimal elev ref', 'Constraint');
xlim([0 20]);

subplot(2,1,2); 
hold on
grid on
plot(pitch_data(1,:), pitch_data(2,:)*(180/pi), 'LineWidth', 1)
plot(t, u1*(180/pi), 'r', 'LineWidth', 1)
xlabel('Time [s]')
ylabel('Angle [rad]')
legend('Pitch ref', 'Optimal pitch ref');
xlim([0 20]);




