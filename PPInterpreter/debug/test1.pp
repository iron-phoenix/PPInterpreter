# rootN.pp
# ��������� ���������� ������? ����������� ��������� a=0
b=0
c=0
read a
read b
read c
if a != 0:
    d=b*b-4*a*c
    if d > 0:
        print 2
    end
    if d == 0:
        print 1
    end
    
    if d < 0:
        print 0
    end
end

if a == 0:
    if b == 0:
        if c == 0:
            print -1 # ��� ����������� �������������
        end
        if c != 0:
            print 0
        end
    end
    if b != 0:
        print 1
    end
end