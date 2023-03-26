close all;
clear all;
clc;
workspace;

%% Prende i dati dal file
filename = '.\scope_19.csv';
delimiter = ',';
startRow = 3;
formatSpec = '%f%f%[^\n\r]';
fileID = fopen(filename,'r');
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'TextType', 'string', 'EmptyValue', NaN, 'HeaderLines' ,startRow-1, 'ReturnOnError', false, 'EndOfLine', '\r\n');
fclose(fileID);
DATA = [dataArray{1:end-1}];
clearvars filename delimiter startRow formatSpec fileID dataArray ans;

%% Plot dei dati

% plot(DATA(:,1),DATA(:,2),"LineWidth",1.5);
% ylabel("Tensione [V]");
% xlabel("Tempo [s]");
% title("Forma d'onda al morsetto invertente v_-");
% hold on;
% grid on;

%% Valutazione della costante di tempo

% myfittype = fittype('A + B*mod((x - C)/D,1)','indep','x','coef',{'A','B','C','D'})
% 
% f = fit(DATA(:,1),DATA(:,2),myfittype)
% 
% plot(f,DATA(:,1),DATA(:,2));

curveFitter(DATA(:,1),DATA(:,2));