function answer = error_for_trapezoid_method_diff(f, a, b, n)
    % Получим таблицу с шагом h
    h = (b - a) / n;
    xx = a : h : b;
    yy = zeros(1, n);
    
    for i = 1 : length(xx)
        yy(i) = subs(f, xx(i));
    end
    
    % Получим значения для второй производной
    d = diff(diff(f));
    d_yy = zeros(1, n);
    
    for i = 1:length(xx)
        d_yy(i) = subs(d, xx(i));
    end
    
    % Получим погрешность
    answer = h^3 * n / 12 * max(abs(d_yy));