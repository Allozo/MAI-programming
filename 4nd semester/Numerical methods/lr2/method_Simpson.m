function answer = method_Simpson(f, a, b, n)
    % Получим таблицу с шагом h
    h = (b - a) / n;
    xx = a : h : b;
    yy = zeros(1, n);

    for i = 1 : length(xx)
        yy(i) = subs(f, xx(i));
    end
    
    part_1 = yy(1) + yy(length(xx));
    
    part_2 = 0;
    for i = 2 : 2 : (length(xx) - 1)
        part_2 = part_2 + yy(i);
    end 
    
    part_3 = 0;
    for i = 3 : 2 : (length(xx) - 1)
        part_3 = part_3 + yy(i);
    end 
    
    answer = h / 3 * (part_1 + 4 * part_2 + 2 * part_3);