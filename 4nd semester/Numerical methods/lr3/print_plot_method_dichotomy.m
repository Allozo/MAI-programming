function [] = print_plot_method_dichotomy(f, a, b, mass_x)
    figure    
    ezplot(f, [-0.1 1.1])
    title("Метод дихотомии")
    grid on
    hold on
    
    plot([a a], [-5 5])
    plot([b b], [-5 5])
    for i=1:1:length(mass_x)
        plot(mass_x(i), subs(f, mass_x(i)), "r.", 'MarkerSize', 15)
        hold on
    end
    