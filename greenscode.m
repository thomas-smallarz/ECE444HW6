format compact; clear variables;
T = pi/10000; 
% pass/stop-band omegas from requirements
omegas1 = 450; 
omegap1 = 1000; 
omegap2 = 2000; 
omegas2 = 4000;
% pre-warped omegas
omegas1p = tan(omegas1*T/2)
omegap1p = tan(omegap1*T/2)
omegap2p = tan(omegap2*T/2)
omegas2p = tan(omegas2*T/2)

omegas = abs([(omegas1p^2-omegap1p*omegap2p)/(omegas1p*(omegap2p-omegap1p)),...
        (omegas2p^2-omegap1p*omegap2p)/(omegas2p*(omegap2p-omegap1p))])
    
omegap = 1; omegas = min(omegas); alphap = 2.1; alphas = 20;
%K = ceil(log((10^(alphas/10)-1)/(10^(alphap/10)-1))/(2*log(omegas/omegap))) % don't need to calculate this
K = 8;
omegac = omegap/((10^(alphap/10)-1)^(1/(2*K)))
% calculating zeros and poles of CT filter
k = [1:K]; Z = []; P = 1j*omegac*exp(1j*pi*(2*k-1)/(2*K));
bL = omegac^K; aK = 1; L = length(Z); K = length(P);

c1 = (omegap1p*omegap2p-1)/(omegap1p*omegap2p+1);
c2 = (omegap2p-omegap1p)/(omegap1p*omegap2p+1);
Zdig = [ones(1,K-L),-ones(1,K-L)];
for i = 1:K
    Pdig(i,:) = roots([1 2*c1./(1-c2*P(i)) (1+c2*P(i))./(1-c2*P(i))]); 
end
B = bL/aK*prod(1/c2-Z)/prod(1/c2-P)*poly(Zdig(:)');
A = poly(Pdig(:)');
fprintf("B:\n"); disp(B'); fprintf("A:\n"); disp(A');

Omega = linspace(0,pi,1001); H = polyval(B,exp(1j*Omega))./polyval(A,exp(1j*Omega));
plot(Omega/T,abs(H),'k-');