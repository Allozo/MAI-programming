function answer = count_step_for_method(error_method, f, a, b, e)
    n = 1;
    new_e = 100;
    
    while new_e > e
        n = n * 2;
        new_e = error_method(f, a, b, n);
    end
    answer = n;