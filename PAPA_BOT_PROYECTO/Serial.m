function Serial(Inpot)


delete(instrfind({'port'},{'COM11'}));
delete(instrfind({'port'},{'COM12'}));

PS = serial('COM12','BaudRate',9600);

fopen(PS);

b = Inpot;

disp(b);

fwrite(PS,b);

fclose(PS); 

delete(PS);

clear PS;

end

