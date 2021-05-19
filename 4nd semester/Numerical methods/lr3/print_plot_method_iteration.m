function [] = print_plot_method_iteration(f, a, b, mass)
    figure    
    ezplot(f, [0.29 0.51])
    title("Метод итераций")
    hold on
    
    for i=1:1:(length(mass) - 1)
        xi = mass(i);
        xi1 = mass(i+1);
        fi = subs(f, xi);
        fi1 = subs(f, xi1);
        plot([xi xi1], [fi fi], "r--")
        plot([xi1 xi1], [fi fi1], "r--")
    end