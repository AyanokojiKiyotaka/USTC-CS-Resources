function [x k]=EqtsSOR(A,b,x0,omiga,eps)
%���ɳڣ�SOR,Successive Over-Relaxation��������������Է�����Ax=b
%[x k]=EqtsSOR(A,b,x0,eps)
%x:��������������
%k:��������
%A:ϵ������
%b:������
%x0:������ʼֵ��������
%omiga:�ɳ����ӣ���ȱʡ��ȱʡֵΪ1����ΪGS������
%eps:����ޣ���ȱʡ��ȱʡֵΪ0.5e-6
%
%Ӧ�þ���:
%A=[4 3 0;3 4 -1;0 -1 4];b=[24;30;-24];x0=[1;1;1];omiga=1.25;
%[x k]=EqtsSOR(A,b,x0,omiga,0.5e-6)
%x=EqtsSOR(A,b,x0)

if nargin==4
eps=0.5e-6;
end
if nargin==3
omiga=1;
eps=0.5e-6;
end

%����������
n=length(b);
if size(A,1) ~= n || n ~= length(x0)
disp('�����������');
x=' ';
k=' ';
return;
end

%�������
k=0;
x=zeros(n,1);
while 1
k=k+1;
for i=1:n
z=0;
for j=1:i-1
z=z+A(i,j)*x(j);
end
for j=i+1:n
z=z+A(i,j)*x0(j);
end
x(i)=(1-omiga)*x0(i)+omiga*(b(i)-z)/A(i,i);
end
if norm(x-x0)<=eps || k==30
break;
end
x0=x;
end

if k==30
disp('��������̫�࣡')
x=' ';
end

return; 