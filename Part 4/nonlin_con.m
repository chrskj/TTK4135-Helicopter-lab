function [c_neq, ceq] = nonlin_con(z)
global N  alpha beta lambda_t mx

c_neq = zeros(N, 1);

for k = 1:N
    travel = z(1 + (k-1)*mx);
    elev = z(5 + (k-1)*mx);
    
    
    c_neq(k) = alpha * exp(-beta*(travel - lambda_t)^2) - elev;

end


ceq = [];