
-- create database cdcquery default character set utf8;

use cdcquery;
drop table if exists repay_realtime_pubtrandef;
create table repay_realtime_pubtrandef
(
	batchno   	char    ( 32 ) not null comment '批次号',
	seqno     	int      				 comment  '运行顺序',
	trandate  	char    ( 10 )  		 comment  '交易日期',
	sysdate   	char    ( 10 ) 			 comment  '系统日期' ,
  	serseqno  	int          			comment  '主机流水号',
  	dbrc      	char    (  4 ) not null  comment  '借方机构',
  	dbaccount 	char    ( 32 ) not null  comment  '借方账号',
  	cbrc      	char    (  4 ) not null  comment  '贷方机构',
  	craccount 	char    ( 32 ) not null  comment  '贷方账号',
  	amt       	decimal (16,2)           comment  '交易金额',
   	keyword   	char    (100 ) not null  comment  '顺序号',
   	channelid 	char    (  2 )           comment  '交易渠道',
   	statcode  	char    ( 10 )           comment  '分析代码',
   	clsprdcode	char    (  7 )           comment  '清算产品',
  	memocode  	char    (  4 )           comment  ' 摘要码',
	infocode  	char    ( 20 )           comment  '统计代码',
   	cdname    	char    ( 50 )           comment  '代码名称',
   	description      	char    (100 )     comment  '交易说明',
   	stat      	char    (  2 ) not null  comment  '状态位',
   	errmsg    	char    (100 )           comment  '错误说明',
  	memo1     	char    ( 40 )           comment  ' 保留位1',
  	memo2     	char    ( 40 )           comment  '保留位2',
   	amt1      	decimal (16,2)           comment  '保留位3',
 	amt2      	decimal (16,2)          comment  '保留位4',
	modifytime	TIMESTAMP				comment  'db2的创建时间'  -- 多的字段
)comment="CDC还款实时def表";
create unique index repay_realtime_pubtrandef_idx on repay_realtime_pubtrandef ( batchno,memocode,keyword );
create index repay_realtime_pubtrandef_idx2 on repay_realtime_pubtrandef ( trandate,batchno,memocode,keyword );
create index repay_realtime_pubtrandef_idx3 on repay_realtime_pubtrandef ( trandate,dbaccount );

 drop table if exists repay_realtime_pubtranext;
create table repay_realtime_pubtranext
(
   
	batchno   	char    ( 32 ) not null comment  '批次号' ,
  	memocode  	char    (  4 ) not null comment  '摘要码' ,
	keyword   	char    (100 ) not null comment  '顺序号' ,
  	trandate  	char    ( 10 )          comment  '主机日期' ,
  	frntdate  	char    ( 10 )          comment  '前置日期' ,
  	serseqno  	int                     comment  '主机流水号' ,
 	channel   	char    (  2 )          comment  '交易来源' ,
 	openbrc   	char    (  9 )          comment  '开户机构' ,
	profitbrc 	char    (  9 )          comment  '核算机构' ,
  	cnapsbankno	char    ( 12 )          comment  '对手行行号' ,
 	accptbrcname1	char    ( 60 )      comment  '对手行名称' ,
 	bmszh     	char    ( 32 )          comment  '对手行转账账号' ,
	bmshm     	char    ( 60 )          comment  '对手行转账户名' ,
	backcnapsno	char    ( 12 )          comment  '我行行号' ,
  	accptbrcname2	char    ( 60 )     comment  ' 我行行名' ,
  	bmstxtype 	char    (  5 )          comment  '业务类型' ,
 	bmsywzlm  	char    (  5 )          comment  '业务种类' ,
 	amt1      	decimal (16,2)          comment  '保留金额1' ,
  	amt2      	decimal (16,2)          comment  '保留金额2' ,
 	amt3      	decimal (16,2)          comment  '保留金额3' ,
 	memo1     	char    (  1 )          comment  '备注字段1' ,
 	memo2     	char    ( 60 )          comment  '备注字段2' ,
 	memo3     	char    (128 )          comment  '备注字段3' ,
 	memo4     	varchar (256 )          comment  '备注字段4' ,
 	memo5     	varchar (512 )    		comment  '备注大字段'     ,
	modifytime	TIMESTAMP				comment  'db2的创建时间'   -- 多的字段
)comment="CDC还款实时ext表";
 
create unique index repay_realtime_pubtranext_idx on repay_realtime_pubtranext ( batchno,memocode,keyword );
create index repay_realtime_pubtranext_idx2 on repay_realtime_pubtranext ( trandate,serseqno );
 
 drop table if exists repay_batch_pubtrandef;
create table repay_batch_pubtrandef
(
	batchno   	char    ( 32 ) not null comment '批次号',
	seqno     	int      				 comment  '运行顺序',
	trandate  	char    ( 10 )  		 comment  '交易日期',
	sysdate   	char    ( 10 ) 			 comment  '系统日期' ,
  	serseqno  	int          			comment  '主机流水号',
  	dbrc      	char    (  4 ) not null  comment  '借方机构',
  	dbaccount 	char    ( 32 ) not null  comment  '借方账号',
  	cbrc      	char    (  4 ) not null  comment  '贷方机构',
  	craccount 	char    ( 32 ) not null  comment  '贷方账号',
  	amt       	decimal (16,2)           comment  '交易金额',
   	keyword   	char    (100 ) not null  comment  '顺序号',
   	channelid 	char    (  2 )           comment  '交易渠道',
   	statcode  	char    ( 10 )           comment  '分析代码',
   	clsprdcode	char    (  7 )           comment  '清算产品',
  	memocode  	char    (  4 )           comment  ' 摘要码',
	infocode  	char    ( 20 )           comment  '统计代码',
   	cdname    	char    ( 50 )           comment  '代码名称',
   	description      	char    (100 )     comment  '交易说明',
   	stat      	char    (  2 ) not null  comment  '状态位',
   	errmsg    	char    (100 )           comment  '错误说明',
  	memo1     	char    ( 40 )           comment  ' 保留位1',
  	memo2     	char    ( 40 )           comment  '保留位2',
   	amt1      	decimal (16,2)           comment  '保留位3',
 	amt2      	decimal (16,2)          comment  '保留位4' 
)comment="CDC还款批量def表";
create unique index repay_batch_pubtrandef_idx on repay_batch_pubtrandef ( batchno,memocode,keyword );
create index repay_batch_pubtrandef_idx2 on repay_batch_pubtrandef ( trandate,batchno,memocode,keyword );
create index repay_batch_pubtrandef_idx3 on repay_batch_pubtrandef ( trandate,dbaccount );


drop table if exists repay_batch_pubtranext;
create table repay_batch_pubtranext
(
	batchno   	char    ( 32 ) not null comment  '批次号' ,
  	memocode  	char    (  4 ) not null comment  '摘要码' ,
	keyword   	char    (100 ) not null comment  '顺序号' ,
  	trandate  	char    ( 10 )          comment  '主机日期' ,
  	frntdate  	char    ( 10 )          comment  '前置日期' ,
  	serseqno  	int                     comment  '主机流水号' ,
 	channel   	char    (  2 )          comment  '交易来源' ,
 	openbrc   	char    (  9 )          comment  '开户机构' ,
	profitbrc 	char    (  9 )          comment  '核算机构' ,
  	cnapsbankno	char    ( 12 )          comment  '对手行行号' ,
 	accptbrcname1	char    ( 60 )      comment  '对手行名称' ,
 	bmszh     	char    ( 32 )          comment  '对手行转账账号' ,
	bmshm     	char    ( 60 )          comment  '对手行转账户名' ,
	backcnapsno	char    ( 12 )          comment  '我行行号' ,
  	accptbrcname2	char    ( 60 )     comment  ' 我行行名' ,
  	bmstxtype 	char    (  5 )          comment  '业务类型' ,
 	bmsywzlm  	char    (  5 )          comment  '业务种类' ,
 	amt1      	decimal (16,2)          comment  '保留金额1' ,
  	amt2      	decimal (16,2)          comment  '保留金额2' ,
 	amt3      	decimal (16,2)          comment  '保留金额3' ,
 	memo1     	char    (  1 )          comment  '备注字段1' ,
 	memo2     	char    ( 60 )          comment  '备注字段2' ,
 	memo3     	char    (128 )          comment  '备注字段3' ,
 	memo4     	varchar (256 )          comment  '备注字段4' ,
 	memo5     	varchar (512 )    		comment  '备注大字段'   
)comment="CDC还款批量ext表";

create unique index repay_batch_pubtranext_idx on repay_batch_pubtranext ( batchno,memocode,keyword );
create index repay_batch_pubtranext_idx2 on repay_batch_pubtranext ( trandate,serseqno );

 
drop table if exists batch_pubtrandef_tmp;
create table batch_pubtrandef_tmp comment="CDC批量def临时表" as select * from repay_batch_pubtrandef where 1=2;
create unique index batch_pubtrandef_tmp_idx on batch_pubtrandef_tmp ( batchno,memocode,keyword );
create index batch_pubtrandef_tmpidx2 on batch_pubtrandef_tmp ( trandate,batchno,memocode,keyword );
create index batch_pubtrandef_tmpidx3 on batch_pubtrandef_tmp ( trandate,dbaccount );

drop table if exists batch_pubtranext_tmp;
create table batch_pubtranext_tmp  comment="CDC批量ext临时表" as select * from repay_batch_pubtranext where 1=2;
create unique index batch_pubtranext_tmp_idx on batch_pubtrandef_tmp ( batchno,memocode,keyword );
create index batch_pubtranext_tmp_idx2 on batch_pubtrandef_tmp ( trandate,serseqno );

-- ============ 内部 放款

drop table if exists payin_realtime_pubtrandef;
create table payin_realtime_pubtrandef comment="CDC内放款实时def表" as select * from rt_pubtrandef where 1=2;
create unique index payin_realtime_pubtrandef_idx on payin_realtime_pubtrandef ( batchno,memocode,keyword );
create index payin_realtime_pubtrandef_idx2 on payin_realtime_pubtrandef ( trandate,batchno,memocode,keyword );
create index payin_realtime_pubtrandef_idx3 on payin_realtime_pubtrandef ( trandate,dbaccount );

drop table if exists payin_realtime_pubtranext;
create table payin_realtime_pubtranext  comment="CDC内放款实时ext表" as select * from rt_pubtranext where 1=2;
create unique index payin_realtime_pubtranext_idx on payin_realtime_pubtranext ( batchno,memocode,keyword );
create index payin_realtime_pubtranext_idx2 on payin_realtime_pubtranext ( trandate,serseqno );


drop table if exists payin_batch_pubtrandef;
create table payin_batch_pubtrandef comment="CDC内放款批量def表" as select * from pubtrandef where 1=2;
create unique index payin_batch_pubtrandef_idx on payin_batch_pubtrandef ( batchno,memocode,keyword );
create index payin_batch_pubtrandef_idx2 on payin_batch_pubtrandef ( trandate,batchno,memocode,keyword );
create index payin_batch_pubtrandef_idx3 on payin_batch_pubtrandef ( trandate,dbaccount );

drop table if exists payin_batch_pubtranext;
create table payin_batch_pubtranext  comment="CDC内放款批量ext表" as select * from pubtranext where 1=2;
create unique index payin_batch_pubtranext_idx on payin_batch_pubtranext ( batchno,memocode,keyword );
create index payin_batch_pubtranext_idx2 on payin_batch_pubtranext ( trandate,serseqno );



drop table if exists tbl_bfrocred;
create table  tbl_bfrocred
(
	msgid             varchar(35) not null  comment '报文标识号',
	instgpty          varchar(12) not null  comment '发起参与机构',
	txid              varchar(140)          comment '交易标识号',
	accptncdttm       timestamp             comment '委托时间',
	chckdt            varchar(10)           comment '对账日期',
	txnetgdt          varchar(10)           comment '轧差日期',
	txnetgrnd         varchar(2)            comment '轧差场次',
	ccy               varchar(3)            comment '货币符号',
	sttlmamt          decimal(18,2)          comment '结算金额',
	liqdt             varchar(10)           comment '清算日期',
	updatetime        timestamp             comment '更新时间',
	dbtracctname      varchar(240)          comment '付款人户名',
	dbtracctno        varchar(128)          comment '付款人账号',
	dbtrprtry         varchar(4)            comment '付款人账户类型',
	dbtrissr          varchar(140)          comment '付款人开户行名称',
	dbtrctrysubdvsn   varchar(6)            comment '付款人开户行所属城市代码',
	dbtrbrnchid       varchar(12)           comment '付款人开户行所属网银系统行号',
	dbtrmmbid         varchar(12)           comment '付款清算行行号',
	cdtracctname      varchar(240)          comment '收款人户名',
	cdtracctno        varchar(128)          comment '收款人账号',
	credprtry         varchar(4)            comment '收款人账号类型',
	cdtrissr          varchar(140)          comment '收款人开户行名称',
	ctrysubdvsn       varchar(6)            comment '收款人开户行所属城市代码',
	cdtrbrnchid       varchar(12)           comment '收款人开户行所属网银系统行号',
	cdtrmmbid         varchar(12)           comment '收款清算行行号',
	ctgyprtry         varchar(4)            comment '业务类型编码',
	purpprtry         varchar(5)            comment '业务种类编码',
	sysdt             varchar(10)           comment '平台工作日期（人行的当前工作日期）',
	stsid             varchar(4)            comment '业务状态',
	rowsts            varchar(1)            comment '记录状态',
	chcksts           varchar(1)            comment '对账状态',
	remark            varchar(560)          comment '附言',
	addtlinf          varchar(420)          comment '业务拒绝原因',
	endtoendid        varchar(35)           comment '端到端标识号',
	stsrsninf         varchar(1024)         comment '业务回执附言',
	rejectcode        varchar(4)            comment '业务拒绝码',
	npcsysdt          varchar(10)           comment '中心工作日期',
	txnetgmmbid       varchar(12)           comment '轧差清算行行号',
	busiid            varchar(60)           comment '平台流水号',
	modifytime  TIMESTAMP               comment  'db2的创建时间',   -- 多的字段
	primary key (msgid,instgpty)
)comment='实时贷记往账表';

drop table tbl_bcomecred;
create table tbl_bcomecred comment='实时贷记来账表' as select * from  tbl_bfrocred where 1=2;
alter table tbl_bcomecred add constraint pk_tbl_bcomecred primary key (msgid,instgpty);


drop table if exists counter_realtime_tran;
 
CREATE table counter_realtime_tran
    (
        trandate DATE NOT NULL COMMENT '交易日期',
        serseqno INT COMMENT '主机流水号',
        ctxnseq INT COMMENT '子交易流水号',
        trancode VARCHAR(6) COMMENT '交易代码',
        subtrancode VARCHAR(6) COMMENT '子交易代码',
        submark VARCHAR(2) COMMENT '子交易标识',
        brc VARCHAR(9) COMMENT '交易机构',
        openbrc VARCHAR(9) COMMENT '委托机构',
        profitbrc VARCHAR(9) COMMENT '核算机构',
        teller VARCHAR(6) COMMENT '交易柜员',
        rteller VARCHAR(6) COMMENT '复核柜员',
        ateller VARCHAR(6) COMMENT '授权柜员',
        ccy VARCHAR(3) COMMENT '币种',
        tranamt DECIMAL(16,2) COMMENT '发生额',
        cashtranflag CHAR(1) COMMENT '现转标志/钞汇标志 1-现金/现钞 2-转帐/现汇',
        cdflag CHAR(1) COMMENT '借贷标志 :D-借 C-贷',
        subctrlcode VARCHAR(10) COMMENT '科目控制字',
        acctno VARCHAR(32) COMMENT '客户帐号',
        subacctno VARCHAR(32) COMMENT '款项代码',
        subsys VARCHAR(3) COMMENT '子系统',
        name VARCHAR(70) COMMENT '户名',
        customerid VARCHAR(21) COMMENT '客户号',
        customtype CHAR(1) COMMENT '客户类别  1-个人2-对公3-金融',
        acctno1 VARCHAR(32) COMMENT '对方帐号',
        subacctno1 VARCHAR(32) COMMENT '对方款项代码',
        transource VARCHAR(2) COMMENT '交易来源',
        frntno VARCHAR(8) COMMENT '前置机编号',
        termcode VARCHAR(15) COMMENT '终端代码',
        termseq INT COMMENT '终端流水号',
        termdate DATE COMMENT '终端交易日期',
        termtime CHAR(6) COMMENT '终端交易时间',
        acctype CHAR(1) COMMENT '帐别',
        subrectype CHAR(1) COMMENT '帐务类型 0-表外  1-表内',
        effectdate DATE COMMENT '生效日期',
        TIME VARCHAR(26) COMMENT '机器时间',
        voukind VARCHAR(3),
        precharcode VARCHAR(6) COMMENT '冠字代码',
        beginvouno VARCHAR(20) COMMENT '起始凭证号',
        endvouno VARCHAR(20) COMMENT '终止凭证号',
        billdate DATE COMMENT '出票日期',
        cancelstan INT COMMENT '冲正错帐流水号',
        postflag CHAR(1) COMMENT '分录标志 0-非分录流水 1-分录流水',
        cashbox INT COMMENT '尾箱号',
        cashitemno VARCHAR(6) COMMENT '现金项目号',
        trantype CHAR(1) COMMENT '交易类型 0：正常 1：蓝字 2：红字',
        reviewflag CHAR(1) COMMENT '复核状态  0：未复核 1：已复核',
        accmode CHAR(1) COMMENT ' 记帐方式  1-单式记帐 2-复式记帐',
        enlistflag CHAR(1) COMMENT '入明细标志  0.未入明细 1.已入明细',
        subrecmode CHAR(1) COMMENT '入明细方式 0-日间实时 1.单笔  2.汇总',
        enaccflag CHAR(1) COMMENT '入分户标志: 0.未入分户 1.已入分户',
        trankind VARCHAR(8) COMMENT '交易性质: 第一位：开销户性质 0-预置1-开户2-销户  3-挂失补开4-挂失销户',
        busitype CHAR(2) COMMENT '业务种类',
        fstlogflag CHAR(1) COMMENT '主流水标志',
        cancelctrl CHAR(1) COMMENT '冲销控制 0.不能冲销 1.可以冲销',
        prdcode VARCHAR(7) COMMENT '产品代码',
        prdtype VARCHAR(3) COMMENT '产品种类',
        settletype VARCHAR(7) COMMENT '清算种类',
        feetype VARCHAR(8),
        statcode VARCHAR(10) COMMENT '分析代码',
        reserv1 VARCHAR(10) COMMENT '预留字段',
        reserv2 VARCHAR(10) COMMENT '预留字段',
        reserv3 VARCHAR(10) COMMENT ' 预留字段',
        revsubtran VARCHAR(6) COMMENT '冲正子交易代码',
        strintdate DATE COMMENT '起息日期',
        canceltransflag CHAR(1) COMMENT '冲销交易标志 0.正常交易 1.冲销交易',
        cancelflag CHAR(1) COMMENT '被冲销标志 0-未被冲销 1-被冲销',
        clsno VARCHAR(32) COMMENT '销帐编号',
        seqno INT COMMENT '序号',
        rnwseqno INT COMMENT '续存号',
        bal DECIMAL(16,2) COMMENT '帐户余额',
        cardno VARCHAR(19) COMMENT '卡号',
        oppclsno VARCHAR(32) COMMENT '对方销帐编号',
        rate DECIMAL(10,6) COMMENT '利率',
        intamt DECIMAL(16,2) COMMENT '利息金额',
        memocode VARCHAR(4) COMMENT '摘要码',
        memo VARCHAR(40) COMMENT '备注',
        memo1 VARCHAR(108) COMMENT '备用',
        modifytime  TIMESTAMP    comment  'db2的创建时间'  ,  -- 多的字段
        CONSTRAINT counter_idx UNIQUE (trandate, serseqno, ctxnseq)
    )comment='实时柜面还款' ;
    
    