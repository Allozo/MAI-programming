function answer = error_method_runge(method, f, a, b, n)
    val1 = method(f, a, b, n);
    val2 = method(f, a, b, n/2);
    
    p = 100000;
    if isequal(method, @method_trapezoid)
        p = 2;
    end 
    if isequal(method, @method_Simpson)
        p = 4;
    end 
    
    answer = abs(val1 - val2) / (2^p - 1);