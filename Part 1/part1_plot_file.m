clc; clear all; close all;
run('init.m')
load('scope_data_exp1_2');

figure

subplot(1,3,1);
plot(scope_data(1,:), scope_data(6, :), 'LineWidth', 2)
title('Elevation')
xlabel('Time [s]')
ylabel('Angle [deg]')
grid on

subplot(1,3,2)
plot(scope_data(1,:), scope_data(4, :), 'r', 'LineWidth', 2)
title('Pitch')
xlabel('Time [s]')
ylabel('Angle [deg]')
grid on

subplot(1,3,3)
plot(scope_data(1,:), scope_data(2, :), 'g', 'LineWidth', 2)
title('Travel')
xlabel('Time [s]')
ylabel('Angle [deg]')
grid on

set(gcf, 'Position', [500,800,1000,250])