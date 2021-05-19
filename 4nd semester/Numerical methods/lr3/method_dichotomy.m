function answer = method_dichotomy(f, a, b, e)
    med = (a + b)/2;
    mass = (med);
    while abs(subs(f, mass(end))) > e
        med = (a + b)/2;
        if subs(f, med) < 0
            a = med;
        else
            b = med;
        end
        mass(end + 1) = med;
    end
    answer = mass;
    