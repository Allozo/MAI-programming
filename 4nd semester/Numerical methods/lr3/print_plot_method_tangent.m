function [] = print_plot_method_tangent(f, b, mass_x)
    figure    
    l1 = ezplot(f, [0 1]);
    set(l1, 'color', 'r')
    
    grid on;
    hold on
    
    plot(b, subs(f, b), "r.",'MarkerSize', 20)
    hold on
    syms x
    df = diff(f);
    for i=1:1:length(mass_x)
        x0 = mass_x(i);
        y = subs(df, x0) * (x - x0) + subs(f, x0);
        ezplot(y, [-0.1 1.1])
        hold on
    end
    title("Метод касательных")
    