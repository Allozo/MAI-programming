function polynom=newton(xx, yy, n)
    syms x;
    sum = yy(1);
    n = n + 1;
    for k=2:n
        % Посчитаем f(x_1, ..., x_k)
        f_1_k = 0;
        for i=1:k
            denominator = 1;
            for j=1:k
                if j ~= i
                    denominator = denominator * (xx(i) - xx(j));
                end
            end
            f_1_k = f_1_k + yy(i) / denominator;
        end
        
        % Посчитаем произведение (x - x_i)
        mult = 1;
        for i=1:(k-1)
            mult = mult * (x - xx(i));
        end
        sum = sum + f_1_k * mult;
    end
    polynom = sum;