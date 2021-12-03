%% clean up any existing serial port connections
delete(instrfindall)

%% Open serial port
ports_available = serialportlist("Available");
if numel(ports_available) == 1
    s1 = serial(ports_available);    
elseif numel(ports_available) > 1
    % Define here YOUR serial port
    [sidx, tf] = listdlg('PromptString', 'Select your serial port','ListString',ports_available);
    data_port = ports_available(sidx);
    s1 = serial(data_port);
else
    warning('No available serial ports detected')
end

s1.BaudRate=9600;       % Define yere YOUR baud rate (same value in the Serial.Begin of Arduino sketch)
fopen(s1);

%% collect data
% global bool_recording %use global if custom callback function is desired
bool_recording = false;

% setup length of recording in seconds
record_time = 600; % 10 minutes
rate = 2; % how many samples per second are sent from Arduino?
data_length = record_time*rate; % length of data stream needed

temperature_data = zeros(data_length,2); % initialize array so serial read can keep up (sample time, temperature_data)
t = zeros(data_length,1); % array to store matlab times

% create figure to plot real time results
figure('Position', [100, 100, 700, 400]);
n = 1;
while ~bool_recording % wait for user to press "RecordData"
    if n == 1
        c1 = uicontrol('Style','togglebutton','String','RecordData','FontSize', 12, 'Position',[20,20,130,30]);
%         c1.Callback = @recordPushed;     
    elseif c1.Value
        bool_recording = true % toggle variable
    end
    n = n+1;
    drawnow % make sure graphics queue is empty
end
tic % start timing in matlab

n = 1; % starting index

% empty serial backlog. Buffer may be full due to Arduino sending temps
% prior to Matlab data collection.
while (s1.BytesAvailable > 10)
    fread(s1,s1.BytesAvailable);
end

% After buffer is empty find start of message. (newline character == 10)
startline = false;
while ~startline
    A = fread(s1,1) % read one byte at a time and discard. stop when newline is read.
    if A == 10
        startline = true;
    end
end

% begin logging data (first second or so is likely in the buffer already)
while (bool_recording)
    if n == 1
        c2 = uicontrol('Style','togglebutton','String','StopRecording','FontSize', 12, 'Position',[550,20,130,30]);
%         c2.Callback = @stopPushed;
    end
    if s1.BytesAvailable
        SerialInfo=fscanf(s1); % Read stream as string. fscanf reads a full line.
        % Other specifications for reading the stream
        %SerialInfo=fscanf(s1,'%f,%f'); % read two comma separated floats
        %SerialInfo=fscanf(s1,'%f %f'); % read two space separated floats
        
        try
            temperature_data(n,:)=str2num(SerialInfo); % works if data is comma seperated.
            % other syntaxes that may work depending on how fscanf is used
            % if data is space separated,             
            %temperature_data(n,:)=SerialInfo'; 
            
        catch % error storing data into array. Replace with NaN for this time step
            temperature_data(n,2) = [NaN,NaN];
        end
        t(n) = toc; % keep time in Matlab

            if n == 1
                % initialize plotting and link data for redrawing
                l1 = plot((temperature_data(1:n,1)-temperature_data(1,1))/1000,temperature_data(1:n,2), 'LineWidth',2); hold on;
                set(l1, 'XDataSource','(temperature_data(1:n,1)-temperature_data(1,1))/1000');
                set(l1, 'YDataSource','temperature_data(1:n,2)');
                linkdata on;
                xlim([0,600]);
                xticks([0 60 120 180 240 300 360 420 480 540 600]);
                xlabel("time (s)");
                ylim([0,40]);
                ylabel("Degrees Celcius")
                set(gca,'Position',[0.12,0.3,0.8,0.6],'FontSize',12)
                set(gca,'XGrid','on')
                drawnow
            else
                % Update graph with new data. Handle specifications must
                % match exactly based on above if statement.
                refreshdata(findobj(l1,'Type','line','XDataSource','(temperature_data(1:n,1)-temperature_data(1,1))/1000', 'YDataSource','temperature_data(1:n,2)'),'caller');
                drawnow % complete all graphic updates now
            end


        if n == data_length
            % Matlab has recorded for the prescribed time
            disp('Allocated array is filled. Stopping recording')
            bool_recording = false; % triggers end of while loop
        end
        n = n+1; % increment index
    end
    
    if c2.Value
        bool_recording = false; % triggers end of while loop
        if temperature_data(n,2) == 0
            n = n-1; % if stop pressed after n was incremented, but before new data was available
        end
    end

end

%% clean up serial port
delete(instrfindall)