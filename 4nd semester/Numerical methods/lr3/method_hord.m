function answer = method_hord(f, a, b, e)
    mass = [];
    xi = a;
    xi1 = a;
    while (abs(subs(f, xi1)) > e)
        xi = xi1;
        xi1 = xi - subs(f, xi)/(subs(f, b) - subs(f, xi))*(b - xi);
        mass(end + 1) = xi1;
    end
    answer = mass;