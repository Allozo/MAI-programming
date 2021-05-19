function answer = method_iteration(f, a, b, e)
    syms x
    phi = x - 0.2*f; 
    
    now_value = (a + b)/2;
    last_value = 0;
    
    mass = (now_value);
    while subs(f, now_value) > e
        last_value = now_value;
        now_value = subs(phi, mass(end));
        mass(end + 1) = now_value;
    end 
    answer = mass;
    