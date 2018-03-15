close all; clc;

load('scope_data.mat')
load('p3_pitch_data.mat')

figure(1)
subplot(511)
stairs(t,u_opt),grid
ylabel('u')
subplot(512)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(513)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(514)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(515)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('Time [s]'),ylabel('pdot')

figure(2)

% Travel
subplot(2,1,1)
hold on;
grid on;
plot(scope_data(1,:), scope_data(2,:))
plot(t, (x1*(180/pi)))
legend('Travel','Optimal travel')
ylabel('Angle [deg]')
xlim([0 25])

% Pitch
subplot(2,1,2)
hold on;
grid on;
plot(scope_data(1,:), scope_data(4,:))
plot(t, x3*(180/pi))
legend('Pitch', 'Optimal pitch')
ylabel('Angle [deg]')
xlabel('Time [s]')
xlim([0 25])

figure(3)

hold on
grid on
plot(pitch_data(1,:), pitch_data(2,:)*(180/pi), 'LineWidth', 1)
plot(t, u_opt*(180/pi), 'LineWidth', 1)
xlabel('Time [s]')
ylabel('Angle [deg]')
legend('Pitch ref', 'Optimal pitch ref');
xlim([0 25]); %ylim([-0.6 2]);

