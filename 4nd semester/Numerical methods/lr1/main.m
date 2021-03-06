% Зададим таблицу
set_x = [0 0.3       0.6       0.7       0.9      1.2      1.4];
set_y = [1 0.643018 -0.771968 -1.339862 -2.117438 0.591808 9.242752];

% Зададим точки, в которых хотим посчитать 
%  значения интерполяционного многочленв
desired_points = [1.3 0.25];

% Добавим на график точки таблицы

plot(set_x, set_y, 'ko', 'LineWidth', 2);
axis([-1 2 -5 15])
grid on;

% Получим интерполяционный многочлен 
%  с помощью встроенной функции
hold on;
p_true = polyfit(set_x, set_y, 6);
pol = poly2sym(p_true);
fplot(pol, 'b');

% Получим интерполяционный многочлен 
%  с помощью написанной функции
hold on
p_my = newton(set_x, set_y, 6);
fplot(p_my, 'r--','LineWidth',2);

% Получим значения в промежуточных точках 
%  по встроенной функции
yp_1_true = polyval(p_true, 1.3)
yp_2_true = polyval(p_true, 0.25)