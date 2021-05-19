function [] = print_plot_method_hord(f, b, mass_x)
    figure    
    ezplot(f, [-0.1 1.1])
    title("Метод хорд")
    hold on
    for i=1:1:length(mass_x)
        plot([mass_x(i), b], [subs(f, mass_x(i)), subs(f, b)])
        hold on
    end
    