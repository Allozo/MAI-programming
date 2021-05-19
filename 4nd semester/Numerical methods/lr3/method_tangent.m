function answer = method_tangent(f, b, e)
    mass = (b);
    df = diff(f);
    while abs(subs(f, mass(end))) > e
        xi = mass(end);
        xi1 = xi - subs(f, xi)/subs(df, xi);
        mass(end + 1) = xi1;
    end
    answer = mass;
    