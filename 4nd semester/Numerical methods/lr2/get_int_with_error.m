function answer = get_int_with_error(method, f, a, b, e)
    n = 1;
    new_e = 100;
    
    while abs(new_e) > e
        n = n * 2;
        val = method(f, a, b, n);
        new_e = error_method_runge(method, f, a, b, n);
        
    end
    answer = [val n];