function answer = method_trapezoid(f, a, b, n)
    % Получим таблицу с шагом h
    h = (b - a) / n;
    xx = a : h : b;
    yy = zeros(1, n);

    for i = 1 : length(xx)
        yy(i) = subs(f, xx(i));
    end
   
    part_sum = 0;
    for i = 2:(length(xx) - 1)
        part_sum = part_sum + yy(i);
    end 
    answer = h / 2 * (yy(1) + 2 * part_sum + yy(length(xx)));
    