clc,clear
% 反演方法测试
%% 理论预设值/真实值
data = textread('data.txt');
q = data(:,1);
d = data(:,2);
R = data(:,3);
Pt = data(:,4);
dfw = data(:,5);

s10 = 4;% 参数的初始值
s20 = 2;
s30 = 0.5;
s40 = -0.5;

plotx = dfw;% 要绘制的x

%% PSO反演
% 初始条件
D = 4;% 变量数，求解维度
N  = 100;% 粒子数
c1 = 2.5;% 学习因子1
c2 = 2.5;% 学习因子2
Gk = 40;% 最大次数
Wi = 0;% 惯性权值
Wini = 0.9;% 初始惯性权值
Wend = 0.2;% 最终惯性权值
IterMax = 1000;% 允许的最大迭代次数
tol = 1.0e-2;% 设置精度
% 变量初始值
xi = zeros(D, N);% 粒子位置
vi = zeros(D, N);% 粒子速度
fiti = zeros(1,N);% 每个粒子的适应度
pbest = zeros(D, N);% 个体最优方案
gbest = zeros(D, 1);% 整体最优方案
pbest_error = zeros(1,N);% 个体最优适应度
gbest_error = 0;% 整体最优适应度
% 范围圈定
Vmax = 0.01;% 最大速度
% 4; 2; 0.5; -0.5;
Xmin = [1; 1; 0.1; -1.0];% 参数范围限定-1 * ones(D,1)
Xmax = [6; 4; 1.2; -0.01];

%%
% -------- %
figure
subplot(2,1,1);
h1 = animatedline;xlabel('Iteration Number'),ylabel('Error'),grid on;
p1 = gca;
p1.YScale = 'log';
% h1 = gca;
subplot(2,1,2);
% plot(plotx,q,'r-');xlabel('dfw'),ylabel('q');
plot(q,'r-');xlabel('点'),ylabel('q');
h2 = gca;

% -------- %
% 初始化位置与速度(可以限定位置和速度的范围)
for i=1:D
    for j=1:N
        xi(i,j) = randn * (Xmax(i) - Xmin(i)) + Xmin(i); %随机初始化位置
        vi(i,j) = randn * Vmax; %随机初始化速度 randn * Vmax * 2 - Vmax
    end
end

% 计算适应度,初始化pbest和gbest
x_ref = q;
for i = 1:N
    x_cal = fun_f(d,R,Pt,dfw, xi(1,i), xi(2,i), xi(3,i), xi(4,i));
    fiti(1,i) = fun_fitness(x_ref, x_cal);
end
pbest_error = fiti;
gbest_error = min(fiti);
pbest = xi;
for i = 1:N
    if pbest_error(1,i) <= gbest_error
        gbest = pbest(:,i);
    end
end

% PSO迭代
Error = gbest_error;
for iter = 1:IterMax
    % 惯性权值
    if iter > Gk
        Wi = Wend;
    else
        Wi = (Wini - Wend)*(Gk - iter)/Gk + Wend;
    end
%     Wi = 1;
    %
    for i = 1:N
        vi(:,i) = Wi*vi(:,i) + c1 * rand * (pbest(:,i) - xi(:,i)) +...
            c2 * rand * (gbest - xi(:,i));
        % vi越界检查
        for j = 1:D
            if vi(j,i) > Vmax
                vi(j,i) = Vmax;
            end
            if vi(j,i) < -Vmax
                vi(j,i) = -Vmax;
            end
        end
        % --------
        xi(:,i) = xi(:,i) + vi(:,i);
        % xi越界检查
        for j = 1:D
            if xi(j,i) > Xmax(j)
                xi(j,i) = Xmax(j);
            end
            if xi(j,i) < Xmin(j)
                xi(j,i) = Xmin(j);
            end
        end
    end
    % 计算适应度并评价
    for i = 1:N
        x_cal = fun_f(d,R,Pt,dfw, xi(1,i), xi(2,i), xi(3,i), xi(4,i));
        fiti(1,i) = fun_fitness(x_ref, x_cal);
    end
    for i = 1:N
        if pbest_error(1,i) > fiti(1,i)
            pbest_error(1,i) = fiti(1,i);
            pbest(:,i) = xi(:,i);
        end
    end
    [tgbest_error, index] = min(pbest_error);
    if gbest_error > tgbest_error
        gbest_error = tgbest_error;
        gbest = pbest(:,index);
    end
    
    Error = vertcat(Error, gbest_error);
    
    %% 动态绘图
    
    addpoints(h1,iter,gbest_error);
    drawnow;
    
    hold(h2,'on');
    if exist('p2','var')
        delete(p2);
    end
    ycal = fun_f(d,R,Pt,dfw, gbest(1), gbest(2), gbest(3), gbest(4));
    %p2 = plot(h2,plotx,ycal,'k-');
    p2 = plot(h2,ycal,'k-');
    legend(h2,'Origin','Inversion');
    drawnow;
    pause(0.005);
    %%
    if gbest_error < tol
        flag = 0;
        break;
    end
end
if iter == IterMax
    flag = 1;
end

figure;
plot(q,'ko');
hold on;
plot(ycal,'r*');
hold off;
xlabel('x'),ylabel('y'),title('最终目标拟合结果对比'),legend('原始','拟合');

disp('拟合系数:');
disp(gbest);
