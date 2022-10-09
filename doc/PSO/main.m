clc,clear
% ���ݷ�������
%% ����Ԥ��ֵ/��ʵֵ
data = textread('data.txt');
q = data(:,1);
d = data(:,2);
R = data(:,3);
Pt = data(:,4);
dfw = data(:,5);

s10 = 4;% �����ĳ�ʼֵ
s20 = 2;
s30 = 0.5;
s40 = -0.5;

plotx = dfw;% Ҫ���Ƶ�x

%% PSO����
% ��ʼ����
D = 4;% �����������ά��
N  = 100;% ������
c1 = 2.5;% ѧϰ����1
c2 = 2.5;% ѧϰ����2
Gk = 40;% ������
Wi = 0;% ����Ȩֵ
Wini = 0.9;% ��ʼ����Ȩֵ
Wend = 0.2;% ���չ���Ȩֵ
IterMax = 1000;% ���������������
tol = 1.0e-2;% ���þ���
% ������ʼֵ
xi = zeros(D, N);% ����λ��
vi = zeros(D, N);% �����ٶ�
fiti = zeros(1,N);% ÿ�����ӵ���Ӧ��
pbest = zeros(D, N);% �������ŷ���
gbest = zeros(D, 1);% �������ŷ���
pbest_error = zeros(1,N);% ����������Ӧ��
gbest_error = 0;% ����������Ӧ��
% ��ΧȦ��
Vmax = 0.01;% ����ٶ�
% 4; 2; 0.5; -0.5;
Xmin = [1; 1; 0.1; -1.0];% ������Χ�޶�-1 * ones(D,1)
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
plot(q,'r-');xlabel('��'),ylabel('q');
h2 = gca;

% -------- %
% ��ʼ��λ�����ٶ�(�����޶�λ�ú��ٶȵķ�Χ)
for i=1:D
    for j=1:N
        xi(i,j) = randn * (Xmax(i) - Xmin(i)) + Xmin(i); %�����ʼ��λ��
        vi(i,j) = randn * Vmax; %�����ʼ���ٶ� randn * Vmax * 2 - Vmax
    end
end

% ������Ӧ��,��ʼ��pbest��gbest
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

% PSO����
Error = gbest_error;
for iter = 1:IterMax
    % ����Ȩֵ
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
        % viԽ����
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
        % xiԽ����
        for j = 1:D
            if xi(j,i) > Xmax(j)
                xi(j,i) = Xmax(j);
            end
            if xi(j,i) < Xmin(j)
                xi(j,i) = Xmin(j);
            end
        end
    end
    % ������Ӧ�Ȳ�����
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
    
    %% ��̬��ͼ
    
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
xlabel('x'),ylabel('y'),title('����Ŀ����Ͻ���Ա�'),legend('ԭʼ','���');

disp('���ϵ��:');
disp(gbest);
