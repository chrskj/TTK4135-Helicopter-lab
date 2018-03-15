close all; clc;

load('p2_data.mat')

figure(1)
subplot(511)
stairs(t,u),grid
ylabel('u')
ylim([-1 1])
subplot(512)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
ylim([-5 5])
subplot(513)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
ylim([-1 1])
subplot(514)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
ylim([-1 1])
subplot(515)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')
ylim([-1 1])

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
