clear, clc
n = 8;
a = 1;
b = 2;
e = 0.01;

syms x;
f = exp(x) / x;

% 1-3
% Получим значения интегралов
val1 = method_trapezoid(f, a, b, n);
str=sprintf('Значение интеграла методом трапеций равно %f, для n = %d ', [val1, n]);
disp(str);

val1 = error_for_trapezoid_method_diff(f, a, b, n);
str = sprintf('Значение погрешности равно %f, для n = %d ', [val1, n]);
disp(str);

disp(' ');



% Вычислим интеграл методом Рунге
val1 = method_Simpson(f, a, b, n);
str = sprintf('Значения интеграла методом Симпсона равно %f, для n = %d ', [val1, n]);
disp(str);

val1 = error_for_simpson_method_diff(f, a, b, n);
str = sprintf('Значение погрешности равно %f, для n = %d ', [val1, n]);
disp(str);

disp(' ');

% 4
% Получим количество шагов необходимое для заданной точности
right_n = count_step_for_method(@error_for_trapezoid_method_diff, f, a, b, e);
str = sprintf('Для метода трапеций нужно n = %d или h = %f, для точности e = %.2f', [right_n, (b - a)/right_n, e]);
disp(str);

right_n = count_step_for_method(@error_for_simpson_method_diff, f, a, b, e);
str = sprintf('Для метода Симпсона нужно n = %d или h = %f, для точности e = %.2f', [right_n, (b - a)/right_n, e]);
disp(str);

disp(' ');

disp('---------------------')

disp(' ');

% 5
val1 = method_trapezoid(f, a, b, n / 2);
str=sprintf('Значение интеграла методом трапеций равно %f, для n = %d ', [val1, n / 2]);
disp(str);

val1 = method_trapezoid(f, a, b, n);
str = sprintf('Значение интеграла методом трапеций равно %f, для n = %d ', [val1, n]);
disp(str);

disp(' ');

val1 = method_Simpson(f, a, b, n / 2);
str=sprintf('Значение интеграла методом Симпсона равно %f, для n = %d ', [val1, n / 2]);
disp(str);

val1 = method_Simpson(f, a, b, n);
str = sprintf('Значение интеграла методом Симпсона равно %f, для n = %d ', [val1, n]);
disp(str);

disp(' ');

% 6
error1 = error_method_runge(@method_trapezoid, f, a, b, n);
str = sprintf('Оценка погрешности методом Рунге для метода трапеций (при n = %d и n = %d) будет равна %f', [n, n / 2, error1]);
disp(str)

error1 = error_method_runge(@method_Simpson, f, a, b, n);
str = sprintf('Оценка погрешности методом Рунге для метода Симпсона (при n = %d и n = %d) будет равна %f', [n, n / 2, error1]);
disp(str)

disp(' ')

% 7-8
val1 = get_int_with_error(@method_trapezoid, f, a, b, e);
str = sprintf('По методу трапеций интеграл равен %f, при e = %f и n = %d', [val1(1), e, val1(2)]);
disp(str)

val1 = get_int_with_error(@method_Simpson, f, a, b, e);
str = sprintf('По методу Симпсона интеграл равен %f, при e = %f и n = %d', [val1(1), e, val1(2)]);
disp(str)