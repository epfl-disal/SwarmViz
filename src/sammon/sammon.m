function y = sammon(x)
%#codgen
%
% SAMMON - apply Sammon's nonlinear mapping 
%
%    Y = SAMMON(X) applies Sammon's nonlinear mapping procedure on
%    multivariate data X, where each row represents a pattern and each column
%    represents a feature.  On completion, Y contains the corresponding
%    co-ordinates of each point on the map.  By default, a two-dimensional
%    map is created.  Note if X contains any duplicated rows, SAMMON will
%    fail (ungracefully). 
%
%    [Y,E] = SAMMON(X) also returns the value of the cost function in E (i.e.
%    the stress of the mapping).
%
%    An N-dimensional output map is generated by Y = SAMMON(X,N) .
%
%    A set of optimisation options can also be specified using a third
%    argument, Y = SAMMON(X,N,OPTS) , where OPTS is a structure with fields:
%
%       MaxIter        - maximum number of iterations
%       TolFun         - relative tolerance on objective function
%       MaxHalves      - maximum number of step halvings
%       Input          - {'raw','distance'} if set to 'distance', X is 
%                        interpreted as a matrix of pairwise distances.
%       Display        - {'off', 'on', 'iter'}
%       Initialisation - {'pca', 'random'}
%
%    The default options structure can be retrieved by calling SAMMON with
%    no parameters.
%
%    References :
%
%       [1] Sammon, John W. Jr., "A Nonlinear Mapping for Data Structure
%           Analysis", IEEE Transactions on Computers, vol. C-18, no. 5,
%           pp 401-409, May 1969.
%
%    See also : SAMMON_TEST

%
% File        : sammon.m
%
% Date        : Monday 12th November 2007.
%
% Author      : Gavin C. Cawley and Nicola L. C. Talbot
%
% Description : Simple vectorised MATLAB implementation of Sammon's non-linear
%               mapping algorithm [1].
%
% References  : [1] Sammon, John W. Jr., "A Nonlinear Mapping for Data
%                   Structure Analysis", IEEE Transactions on Computers,
%                   vol. C-18, no. 5, pp 401-409, May 1969.
%
% History     : 10/08/2004 - v1.00
%               11/08/2004 - v1.10 Hessian made positive semidefinite
%               13/08/2004 - v1.11 minor optimisation
%               12/11/2007 - v1.20 initialisation using the first n principal
%                                  components.
%
% Thanks      : Dr Nick Hamilton (nick@maths.uq.edu.au) for supplying the
%               code for implementing initialisation using the first n
%               principal components (introduced in v1.20).
%
% To do       : The current version does not take advantage of the symmetry
%               of the distance matrix in order to allow for easy
%               vectorisation.  This may not be a good choice for very large
%               datasets, so perhaps one day I'll get around to doing a MEX
%               version using the BLAS library etc. for very large datasets.
%
% Copyright   : (c) Dr Gavin C. Cawley, November 2007.
%
%    This program is free software; you can redistribute it and/or modify
%    it under the terms of the GNU General Public License as published by
%    the Free Software Foundation; either version 2 of the License, or
%    (at your option) any later version.
%
%    This program is distributed in the hope that it will be useful,
%    but WITHOUT ANY WARRANTY; without even the implied warranty of
%    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%    GNU General Public License for more details.
%
%    You should have received a copy of the GNU General Public License
%    along with this program; if not, write to the Free Software
%    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
%

% use the default options structure
Initialisation = 'random';

n = 2;

% create distance matrix unless given by parameters
D = euclid(x, x);


% remaining initialisation

N     = size(x, 1);
scale = 0.5/sum(D(:));
D     = D + eye(N);
Dinv  = 1./D;

if strcmp(Initialisation, 'pca')
   [UU,DD] = svd(x);
   y       = UU(:,1:n)*DD(1:n,1:n);
else
   y = randn(N, n);
end

one   = ones(N,n);
d     = euclid(y,y) + eye(N);
dinv  = 1./d;
delta = D - d;
E     = sum(sum((delta.^2).*Dinv));

% get on with it

for i=1:500

   % compute gradient, Hessian and search direction (note it is actually
   % 1/4 of the gradient and Hessian, but the step size is just the ratio
   % of the gradient and the diagonal of the Hessian so it doesn't matter).

   delta    = dinv - Dinv;
   deltaone = delta*one;
   g        = delta*y - y.*deltaone;
   dinv3    = dinv.^3; 
   y2       = y.^2;
   H        = dinv3*y2 - deltaone -2*y.*(dinv3*y) + y2.*(dinv3*one);
   s        = -g(:)./abs(H(:));
   y_old    = y;

   % use step-halving procedure to ensure progress is made

   for j=1:20

      y(:) = y_old(:) + s;

      d     = euclid(y,y) + eye(N);
      dinv  = 1./d;
      delta = D - d;
      E_new = sum(sum((delta.^2).*Dinv));

      if E_new < E

         break;

      else

         s = 0.5*s;

      end

   end

   % bomb out if too many halving steps are required

   if j == 20
      break;
   end

   % evaluate termination criterion

   if abs((E - E_new)/E) < 1E-9
      break;
   end

   % report progress
   E = E_new;

end

% fiddle stress to match the original Sammon paper

E = E*scale;

% all done

function d = euclid(x,y)

d = sqrt(sum(x.^2,2)*ones(1,size(y,1))+ones(size(x,1),1)*sum(y.^2,2)'-2*(x*y'));

