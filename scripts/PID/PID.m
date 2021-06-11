%% PID
signals = importdata('PID_1.txt');
t_total = 30;
t = 0:t_total/(length(signals)-1):t_total;
setpoint = 13*ones(size(t));

% x(t)
figure()
hold on
plot(t,signals(:,1))
plot(t,setpoint)
title('x(t) planta con control PID')
xlabel('t (segundos)')
ylabel('distancia (cm)')
legend('x(t)','setpoint')
grid('minor')
hold off

%señal de control

figure()
hold on
plot(t,signals(:,3))
title('u_{c}(t) planta con control PID')
xlabel('t (segundos)')
ylabel('u_{c}(t) (grados)')
legend('u_{c}(t)')
grid('minor')
hold off

%error 

figure()
hold on
plot(t,signals(:,2))
title('Error de la  planta con control PID')
xlabel('t (segundos)')
ylabel('e(t)')
legend('e(t)')
grid('minor')
hold off
