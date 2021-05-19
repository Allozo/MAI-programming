syms x;
f = 3^x + 2 * x - 2;
a = 0;
b = 1;
e = 0.001;

% Метод хорд
mass_x = method_hord(f, a, b, e);
disp("Выведем последовательность точек, по методу хорд:")
disp(mass_x)
print_plot_method_hord(f, b, mass_x)
disp("")

% Метод касательных
mass_x = method_tangent(f, b, e);
disp("Выведем последовательность точек, по методу касательных:")
disp(mass_x)
print_plot_method_tangent(f, b, mass_x)
disp("")

% Метод половинного деления
mass_x = method_dichotomy(f, a, b, e);
disp("Выведем последовательность точек, по методу половинного деления:")
disp(mass_x)
print_plot_method_dichotomy(f, a, b, mass_x)
disp("")

% Метод итераций
mass_x = method_iteration(f, a, b, e);
disp("Выведем последовательность точек, по методу итераций:")
disp(mass_x)
print_plot_method_iteration(f, a, b, mass_x)
disp("")
