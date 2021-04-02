function answer = error_for_simpson_method_diff(f, a, b, n)
    % Получим таблицу с шагом h
    h = (b - a) / n;
    xx = a : h : b;
    yy = zeros(1, n);
    
    for i = 1 : length(xx)
        yy(i) = subs(f, xx(i));
    end
    
    % Получим значения для второй производной
    d = diff(diff(diff(diff(f))));
    dddd_yy = zeros(1, n);
    
    for i = 1:length(xx)
        dddd_yy(i) = subs(d, xx(i));
    end
    
    answer = h^4 * (b - a) / 180 * max(abs(dddd_yy));