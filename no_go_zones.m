% in freq!!

alphap = 2;
alphas = 20;
ripplep = 1/db2mag(alphap);
ripples = 1/db2mag(alphas);
top_of_plot = 1.2;

if fs1>fp1;fprintf("WARNIGN: lower stop band limit is higher than Lower Pass band limit!\n");end
if fp2<fp1;fprintf("WARNING: upper pass band limit is higher than lower!\n");end
if fp2>fs2;fprintf("WARNING: upper pass band limit is higher than upper stop band limit!\n");end
if ripples>ripplep;fprintf("WARNING: top of stop band ripple is higher than bottom of pass band ripple!\n");end

rectangle('Position',[0 ripples fs1 top_of_plot-ripples],'FaceColor','k');
rectangle('Position',[fp1 0 (fp2-fp1) ripplep],'FaceColor','k');
rectangle('Position',[fp1 1 (fp2-fp1) top_of_plot-1],'FaceColor','k');
rectangle('Position',[fs2 ripples fs2*top_of_plot top_of_plot-ripples],'FaceColor','k');



