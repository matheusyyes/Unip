create database teatro;
use teatro;

create table tb_convidado
(
id int not null primary key auto_increment,
tb_convidado_nome varchar (128) not null,
tb_convidado_rg char(9) not null,
tb_convidado_email varchar(128) not null,
tb_convidado_tel varchar(21) not null
);

create table tb_usuarios (
id int primary key auto_increment,
nome varchar (255),
telefone varchar (255),
email varchar (255),
rg varchar (255));



select * from tb_convidado; 

select * from tb_usuarios;

-- UPDATE tb_usuarios SET lugar_x='5', lugar_y='9' where rg = '528729858';


