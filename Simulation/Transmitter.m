close all; clear; clc;

fc = 10; % carrier frequency in Hz
fs = 100*fc; % sample at 100 times the carrier frequency
dt = 1/fs; %time interval
t = -0.5:dt:1.5; % time in seconds
L = length(t); % Length of the signal

sinusoid = cos(2*pi*fc*t); % carrier signal
modulator = rectpuls(t-0.5,1); % modulating signal
c = sinusoid .* modulator; % modulated signal

figure(1)
subplot(311), plot(t,sinusoid);
axis([-0.5,1.5,-1.2, 1.2])
xlabel('Time (s)')
title('Carrier Signal')

subplot(312), plot(t,modulator);
axis([-0.5,1.5,-0.2, 1.2])
xlabel('Time (s)')
title('Modulating Signal')
grid 'on'

subplot(313), plot(t,c);
axis([-0.5,1.5,-1.2, 1.2])
xlabel('Time (s)','fontsize',11)
title('Modulated Signal')
grid 'on'

% Generate a test message and convert it to a bistream
test_message = "Hi!";
test_message = dec2bin(double(char(test_message)), 8);
[num_chars, bits] = size(test_message);
bitstream = test_message(1:(num_chars*bits))

figure;
matched_wave = zeros(length(sinusoid));
wave=str2num(test_message(:))
T=1/(1/2); % 0.5 Hz rate gives each bit 2 seconds of play time
t=0:T:(numel(wave)-1)*T;
stairs(t,wave,'blue','linewidth',1);


    
