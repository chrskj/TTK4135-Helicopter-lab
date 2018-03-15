global lambda_t mx alpha beta N 

load('scope_data_open_loop.mat');

figure(1)
% Travel
subplot(3,1,1)
hold on;
grid on;
plot(scope_data_open_loop(1,:), scope_data_open_loop(2,:)*(180/pi))
plot(t, (x1*(180/pi)), 'r')
legend('Travel','Optimal travel')
ylabel('Angle [deg]')
xlim([0 25])
% Pitch
subplot(3,1,2)
hold on;
grid on;
plot(scope_data_open_loop(1,:), scope_data_open_loop(4,:)*(180/pi))
plot(t, x3*(180/pi), 'r')
legend('Pitch', 'Optimal pitch')
ylabel('Angle [deg]')
xlim([0 25])
% Elevation
subplot(3,1,3)
hold on;
grid on;
plot(scope_data_open_loop(1,:), scope_data_open_loop(6,:)*(180/pi))
plot(t, x5*(180/pi), 'r')
plot(t, constraint*(180/pi), 'm', 'LineWidth', 1)
legend('Elevation', 'Optimal Elevation', 'Constraint')
ylabel('Angle [deg]')
xlabel('Time [s]')
xlim([0 25])


