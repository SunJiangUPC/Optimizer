function q = fun_f(d,R,Pt,dfw,s1,s2,s3,s4)
% 自变量：d,R,Pt,dfw
% 参数：s1,s2,s3,s4
% 函数
q = s1 * d.^s2 ./ (R.^s3) .* Pt .*dfw.^s4;

end