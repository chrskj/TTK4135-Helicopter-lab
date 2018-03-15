clc; clear; close all;
run ('template_problem.m')

[K,S,e] = dlqr(A1, B1, Q1, P1)

size([t' x_opt])
size([t' u_opt])

Q1 = diag([10 1 1 1]);