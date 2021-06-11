%% data1 
distance = importdata('datos_para_identificacion1.txt');
distance = nonzeros(distance);
distance = distance - distance(1);
t = 0:1.8/(length(distance)-1):1.8;

angle = 115*ones(size(distance));
angle(1) = 125;
figure()
subplot(2,1,1)
plot(t,distance)
title('Distancia vs tiempo')
xlabel('t (segundos)')
ylabel('Distancia (cm)')
legend('x(t)')
grid('minor')

subplot(2,1,2)
plot(t, angle)
title('Angulo vs tiempo')
xlabel('t (segundos)')
ylabel('Angulo (°)')
legend('alpha(t)')
grid('minor')


% Regresion 

theta0 = 100;

f = @(theta) theta*transpose(t).^(2);
objective = @(theta) sum(distance - f(theta)).^2;
theta = fmincon(objective, theta0);

figure()
hold on
plot(t,distance, '*')
plot(t,f(theta))
title('x(t) estimada con la distribucion de los datos')
xlabel('t (segundos)')
ylabel('distancia')
legend('Distribucion de los datos', 'x(t) estimada')
grid('minor')
hold off

syms t s
Y = laplace(theta*t^2, s);