% ECE 444 HW6
% Fall 2020
% Thomas Smallarz

function [] = GenerateHeader(coef)
    fid = fopen('coef.h','w');
    fprintf(fid,'#define K %d \n',size(coef,1));
    for i = 1:size(coef,3)
        fprintf(fid,'float coef%d[K][3] = { \n',i);
        
        for j = 1:size(coef,1)
            fprintf(fid,"\t{ "); 
            
            for k = 1:size(coef,2)
                
                if k == size(coef,2); fprintf(fid,'%.16f',coef(j,k,i)); 
                else; fprintf(fid,'%.16f, ',coef(j,k,i)); end
                
            end
            
            fprintf(fid,"\t}\n");
        end        
        
        fprintf(fid,'}; \n');
    end
        
    fclose(fid);
end

