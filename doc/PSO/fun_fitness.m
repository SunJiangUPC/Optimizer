function [fitn] = fun_fitness(x_ref, x_cal)
% ��Ӧ�Ⱥ���

fitn = norm(x_ref - x_cal);

end