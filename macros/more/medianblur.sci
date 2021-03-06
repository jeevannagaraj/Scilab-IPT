//Function migration (image list to matrix) for: medianblur
//Generated by migrate.cpp
//Author: Anirudh Katoch
function res = medianblur(varargin)
	select length(varargin)
		case 02 then
			res = il2mat(raw_medianblur(mat2il(varargin(01)), varargin(02)))
		else
			error(39)
	end
endfunction