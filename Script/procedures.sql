


Delimiter //

create procedure cadas_usu (
nome varchar (255),
telefone varchar (255),
email varchar (255),
rg varchar (255)
)
begin
	insert into tb_usuarios (nome,telefone,email,rg) 
						value (nome,telefone,email,rg);
end
//

-- cadastro de convidado --
Delimiter //

create procedure cadas_convidado (
tb_convidado_nome varchar (128),
tb_convidado_rg char(9),
tb_convidado_email varchar(128),
tb_convidado_tel varchar(21)     
)
begin
	insert into tb_convidado (tb_convidado_nome, tb_convidado_rg, tb_convidado_email, tb_convidado_tel) 
						value (tb_convidado_nome, tb_convidado_rg, tb_convidado_email, tb_convidado_tel);
end
//



