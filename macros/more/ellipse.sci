//Function migration (image list to matrix) for: ellipse
//Generated by migrate.cpp
//Author: Anirudh Katoch
function res = ellipse(varargin)
	select length(varargin)
		case 14 then
			res = il2mat(raw_ellipse(mat2il(varargin(01)), varargin(02), varargin(03), varargin(04), varargin(05), varargin(06), varargin(07), varargin(08), varargin(09), varargin(10), varargin(11), varargin(12), varargin(13), varargin(14)))
		else
			error(39)
	end
endfunction