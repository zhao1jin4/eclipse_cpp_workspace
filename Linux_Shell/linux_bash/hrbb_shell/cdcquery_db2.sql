
drop table pubtrandef;
create table  pubtrandef
(
	batchno   	char    ( 32 ) not null ,
	seqno     	int      				 ,
	trandate  	char    ( 10 )  		 ,
	sysdate   	char    ( 10 ) 			 ,
  	serseqno  	int          			 ,
  	dbrc      	char    (  4 ) not null ,
  	dbaccount 	char    ( 32 ) not null ,
  	cbrc      	char    (  4 ) not null ,
  	craccount 	char    ( 32 ) not null ,
  	amt       	decimal (16,2)          ,
   	keyword   	char    (100 ) not null ,
   	channelid 	char    (  2 )          ,
   	statcode  	char    ( 10 )          ,
   	clsprdcode	char    (  7 )          ,
  	memocode  	char    (  4 )          ,
	infocode  	char    ( 20 )          ,
   	cdname    	char    ( 50 )          ,
   	description      	char    (100 )  ,
   	stat      	char    (  2 ) not null ,
   	errmsg    	char    (100 )          ,
  	memo1     	char    ( 40 )          ,
  	memo2     	char    ( 40 )          ,
   	amt1      	decimal (16,2)          ,
 	amt2      	decimal (16,2)          ,
	modifytime	TIMESTAMP default sysdate
);

create unique index  pubtrandef_idx on pubtrandef ( batchno,memocode,keyword );
create index  pubtrandef_idx2 on pubtrandef ( trandate,batchno,memocode,keyword );
create index  pubtrandef_idx3 on pubtrandef ( trandate,dbaccount );
   
COMMENT on table TBL_BFROCRED is '大小额主表' ; 
 COMMENT on column  pubtrandef.batchno   	 is  '批次号';
 COMMENT on column  pubtrandef.seqno     	 is   '运行顺序';
 COMMENT on column  pubtrandef.trandate  	 is   '交易日期';
 COMMENT on column  pubtrandef.sysdate   	 is   '系统日期' ;
 COMMENT on column  pubtrandef.serseqno  	 is  '主机流水号';
 COMMENT on column  pubtrandef.dbrc      	 is   '借方机构';
 COMMENT on column  pubtrandef.dbaccount 	 is   '借方账号';
 COMMENT on column  pubtrandef.cbrc      	 is   '贷方机构';
 COMMENT on column  pubtrandef.craccount 	 is   '贷方账号';
 COMMENT on column  pubtrandef.amt       	 is   '交易金额';
 COMMENT on column  pubtrandef.keyword   	 is   '顺序号';
 COMMENT on column  pubtrandef.channelid 	 is   '交易渠道';
 COMMENT on column  pubtrandef.statcode  	 is   '分析代码';
 COMMENT on column  pubtrandef.clsprdcode	 is   '清算产品';
 COMMENT on column  pubtrandef.memocode  	 is   ' 摘要码';
 COMMENT on column  pubtrandef.infocode  	 is   '统计代码';
 COMMENT on column  pubtrandef.cdname    	 is   '代码名称';
 COMMENT on column  pubtrandef.description  is   '交易说明';
 COMMENT on column  pubtrandef.stat      	 is   '状态位';
 COMMENT on column  pubtrandef.errmsg    	 is   '错误说明';
 COMMENT on column  pubtrandef.memo1     	 is   ' 保留位1';
 COMMENT on column  pubtrandef.memo2     	 is   '保留位2';
 COMMENT on column  pubtrandef.amt1      	 is   '保留位3';
 COMMENT on column  pubtrandef.amt2      	 is  '保留位4';
 COMMENT on column  pubtrandef.modifytime	 is  'db2的创建时间';
  
drop table pubtranext;
create table  pubtranext
( 
	batchno   	char    ( 32 ) not null  ,
  	memocode  	char    (  4 ) not null  ,
	keyword   	char    (100 ) not null  ,
  	trandate  	char    ( 10 )           ,
  	frntdate  	char    ( 10 )           ,
  	serseqno  	int                      ,
 	channel   	char    (  2 )           ,
 	openbrc   	char    (  9 )           ,
	profitbrc 	char    (  9 )           ,
  	cnapsbankno	char    ( 12 )           ,
 	accptbrcname1	char    ( 60 )       ,
 	bmszh     	char    ( 32 )           ,
	bmshm     	char    ( 60 )           ,
	backcnapsno	char    ( 12 )           ,
  	accptbrcname2	char    ( 60 )       ,
  	bmstxtype 	char    (  5 )           ,
 	bmsywzlm  	char    (  5 )           ,
 	amt1      	decimal (16,2)           ,
  	amt2      	decimal (16,2)           ,
 	amt3      	decimal (16,2)           ,
 	memo1     	char    (  1 )           ,
 	memo2     	char    ( 60 )           ,
 	memo3     	char    (128 )           ,
 	memo4     	varchar (256 )           ,
 	memo5     	varchar (512 )    		 ,
	modifytime	TIMESTAMP default sysdate
);

create unique index  pubtranext_idx on pubtranext ( batchno,memocode,keyword );
create index  pubtranext_idx2 on pubtranext ( trandate,serseqno );
 
COMMENT on table pubtranext is '大小额扩展表' ; 
COMMENT on column  pubtranext.batchno   	 is '批次号'  ;
COMMENT on column  pubtranext.memocode  	 is '摘要码'  ;
COMMENT on column  pubtranext.keyword   	 is '顺序号'  ;
COMMENT on column  pubtranext.trandate  	 is '主机日期'  ;
COMMENT on column  pubtranext.frntdate  	 is '前置日期'  ;
COMMENT on column  pubtranext.serseqno  	 is '主机流水号'  ;
COMMENT on column  pubtranext.channel   	 is '交易来源'  ;
COMMENT on column  pubtranext.openbrc   	 is '开户机构'  ;
COMMENT on column  pubtranext.profitbrc 	 is '核算机构'  ;
COMMENT on column  pubtranext.cnapsbankno	 is '对手行行号'  ;
COMMENT on column  pubtranext.accptbrcname1	is '对手行名称'  ;
COMMENT on column  pubtranext.bmszh     	 is '对手行转账账号'  ;
COMMENT on column  pubtranext.bmshm     	 is '对手行转账户名'  ;
COMMENT on column  pubtranext.backcnapsno	 is '我行行号'  ;
COMMENT on column  pubtranext.accptbrcname2	 is  '我行行名'  ;
COMMENT on column  pubtranext.bmstxtype 	 is '业务类型'  ;
COMMENT on column  pubtranext.bmsywzlm  	 is '业务种类'  ;
COMMENT on column  pubtranext.amt1      	 is '保留金额1'  ;
COMMENT on column  pubtranext.amt2      	 is '保留金额2'  ;
COMMENT on column  pubtranext.amt3      	 is '保留金额3'  ;
COMMENT on column  pubtranext.memo1     	 is '备注字段1'  ;
COMMENT on column  pubtranext.memo2     	 is '备注字段2'  ;
COMMENT on column  pubtranext.memo3     	 is '备注字段3'  ;
COMMENT on column  pubtranext.memo4     	 is '备注字段4'  ;
COMMENT on column  pubtranext.memo5     	 is '备注大字段'     ;
COMMENT on column  pubtranext.modifytime	 is 'db2的创建时间'   ;

drop table TBL_BFROCRED;
create table  TBL_BFROCRED
(
	MSGID             VARCHAR(35) not null,
	INSTGPTY          VARCHAR(12) not null,
	TXID              VARCHAR(140),
	ACCPTNCDTTM       TIMESTAMP,
	CHCKDT            VARCHAR(10),
	TXNETGDT          VARCHAR(10),
	TXNETGRND         VARCHAR(2),
	CCY               VARCHAR(3),
	STTLMAMT          NUMERIC(18,2),
	LIQDT             VARCHAR(10),
	UPDATETIME        TIMESTAMP,
	DBTRACCTNAME      VARCHAR(240),
	DBTRACCTNO        VARCHAR(128),
	DBTRPRTRY         VARCHAR(4),
	DBTRISSR          VARCHAR(140),
	DBTRCTRYSUBDVSN   VARCHAR(6),
	DBTRBRNCHID       VARCHAR(12),
	DBTRMMBID         VARCHAR(12),
	CDTRACCTNAME      VARCHAR(240),
	CDTRACCTNO        VARCHAR(128),
	CREDPRTRY         VARCHAR(4),
	CDTRISSR          VARCHAR(140),
	CTRYSUBDVSN       VARCHAR(6),
	CDTRBRNCHID       VARCHAR(12),
	CDTRMMBID         VARCHAR(12),
	CTGYPRTRY         VARCHAR(4),
	PURPPRTRY         VARCHAR(5),
	SYSDT             VARCHAR(10),
	STSID             VARCHAR(4),
	ROWSTS            VARCHAR(1),
	CHCKSTS           VARCHAR(1),
	REMARK            VARCHAR(560),
	ADDTLINF          VARCHAR(420),
	ENDTOENDID        VARCHAR(35),
	STSRSNINF         VARCHAR(1024),
	REJECTCODE        VARCHAR(4),
	NPCSYSDT          VARCHAR(10),
	TXNETGMMBID       VARCHAR(12),
	BUSIID            VARCHAR(60) ,
	modifytime  TIMESTAMP default sysdate
	,primary key (MSGID,INSTGPTY)
);

COMMENT on table TBL_BFROCRED is '超级网银的贷记往账表' ;

COMMENT on column  TBL_BFROCRED.MSGID             is '报文标识号';
COMMENT on column  TBL_BFROCRED.INSTGPTY          is '发起参与机构';
COMMENT on column  TBL_BFROCRED.TXID              is '交易标识号';
COMMENT on column  TBL_BFROCRED.ACCPTNCDTTM       is '委托时间';
COMMENT on column  TBL_BFROCRED.CHCKDT            is '对账日期';
COMMENT on column  TBL_BFROCRED.TXNETGDT          is '轧差日期';
COMMENT on column  TBL_BFROCRED.TXNETGRND         is '轧差场次';
COMMENT on column  TBL_BFROCRED.CCY               is '货币符号';
COMMENT on column  TBL_BFROCRED.STTLMAMT          is '结算金额';
COMMENT on column  TBL_BFROCRED.LIQDT             is '清算日期';
COMMENT on column  TBL_BFROCRED.UPDATETIME        is '更新时间';
COMMENT on column  TBL_BFROCRED.DBTRACCTNAME      is '付款人户名';
COMMENT on column  TBL_BFROCRED.DBTRACCTNO        is '付款人账号';
COMMENT on column  TBL_BFROCRED.DBTRPRTRY         is '付款人账户类型';
COMMENT on column  TBL_BFROCRED.DBTRISSR          is '付款人开户行名称';
COMMENT on column  TBL_BFROCRED.DBTRCTRYSUBDVSN   is '付款人开户行所属城市代码';
COMMENT on column  TBL_BFROCRED.DBTRBRNCHID       is '付款人开户行所属网银系统行号';
COMMENT on column  TBL_BFROCRED.DBTRMMBID         is '付款清算行行号';
COMMENT on column  TBL_BFROCRED.CDTRACCTNAME      is '收款人户名';
COMMENT on column  TBL_BFROCRED.CDTRACCTNO        is '收款人账号';
COMMENT on column  TBL_BFROCRED.CREDPRTRY         is '收款人账号类型';
COMMENT on column  TBL_BFROCRED.CDTRISSR          is '收款人开户行名称';
COMMENT on column  TBL_BFROCRED.CTRYSUBDVSN       is '收款人开户行所属城市代码';
COMMENT on column  TBL_BFROCRED.CDTRBRNCHID       is '收款人开户行所属网银系统行号';
COMMENT on column  TBL_BFROCRED.CDTRMMBID         is '收款清算行行号';
COMMENT on column  TBL_BFROCRED.CTGYPRTRY         is '业务类型编码';
COMMENT on column  TBL_BFROCRED.PURPPRTRY         is '业务种类编码';
COMMENT on column  TBL_BFROCRED.SYSDT             is '平台工作日期（人行的当前工作日期）';
COMMENT on column  TBL_BFROCRED.STSID             is '业务状态';
COMMENT on column  TBL_BFROCRED.ROWSTS            is '记录状态';
COMMENT on column  TBL_BFROCRED.CHCKSTS           is '对账状态';
COMMENT on column  TBL_BFROCRED.REMARK            is '附言';
COMMENT on column  TBL_BFROCRED.ADDTLINF          is '业务拒绝原因';
COMMENT on column  TBL_BFROCRED.ENDTOENDID        is '端到端标识号';
COMMENT on column  TBL_BFROCRED.STSRSNINF         is '业务回执附言';
COMMENT on column  TBL_BFROCRED.REJECTCODE        is '业务拒绝码';
COMMENT on column  TBL_BFROCRED.NPCSYSDT          is '中心工作日期';
COMMENT on column  TBL_BFROCRED.TXNETGMMBID       is '轧差清算行行号';
COMMENT on column  TBL_BFROCRED.BUSIID            is '平台流水号';
COMMENT on column  TBL_BFROCRED.modifytime     is 'db2的创建时间'   ;



drop table TBL_BCOMECRED;
create table TBL_BCOMECRED like TBL_BFROCRED ;
alter table TBL_BCOMECRED add constraint PK_TBL_BCOMECRED primary key (MSGID,INSTGPTY);

COMMENT on table TBL_BCOMECRED is '超级网银的贷记来账表' ;

 
CREATE table glssubtranslog
    (                                 
        trandate DATE NOT NULL       ,
        serseqno INT  NOT　NULL         ,
        ctxnseq INT   NOT　NULL          ,
        trancode VARCHAR(6)          ,
        subtrancode VARCHAR(6)       ,
        submark VARCHAR(2)           ,
        brc VARCHAR(9)                ,
        openbrc VARCHAR(9)           ,
        profitbrc VARCHAR(9)         ,
        teller VARCHAR(6)            ,
        rteller VARCHAR(6)           ,
        ateller VARCHAR(6)           ,
        ccy VARCHAR(3)                ,
        tranamt DECIMAL(16,2)        ,
        cashtranflag CHAR(1)         ,
        cdflag CHAR(1)                ,
        subctrlcode VARCHAR(10)      ,
        acctno VARCHAR(32)           ,
        subacctno VARCHAR(32)        ,
        subsys VARCHAR(3)            ,
        name VARCHAR(70)             ,
        customerid VARCHAR(21)       ,
        customtype CHAR(1)           ,
        acctno1 VARCHAR(32)          ,
        subacctno1 VARCHAR(32)       ,
        transource VARCHAR(2)        ,
        frntno VARCHAR(8)            ,
        termcode VARCHAR(15)         ,
        termseq INT                   ,
        termdate DATE                 ,
        termtime CHAR(6)             ,
        acctype CHAR(1)              ,
        subrectype CHAR(1)           ,
        effectdate DATE              ,
        "TIME" VARCHAR(26)             ,
        voukind VARCHAR(3)            ,
        precharcode VARCHAR(6)       ,
        beginvouno VARCHAR(20)       ,
        endvouno VARCHAR(20)         ,
        billdate DATE                 ,
        cancelstan INT                ,
        postflag CHAR(1)             ,
        cashbox INT                   ,
        cashitemno VARCHAR(6)        ,
        trantype CHAR(1)             ,
        reviewflag CHAR(1)           ,
        accmode CHAR(1)              ,
        enlistflag CHAR(1)           ,
        subrecmode CHAR(1)           ,
        enaccflag CHAR(1)            ,
        trankind VARCHAR(8)          ,
        busitype CHAR(2)             ,
        fstlogflag CHAR(1)           ,
        cancelctrl CHAR(1)           ,
        prdcode VARCHAR(7)           ,
        prdtype VARCHAR(3)           ,
        settletype VARCHAR(7)        ,
        feetype VARCHAR(8)           ,
        statcode VARCHAR(10)         ,
        reserv1 VARCHAR(10)          ,
        reserv2 VARCHAR(10)          ,
        reserv3 VARCHAR(10)          ,
        revsubtran VARCHAR(6)        ,
        strintdate DATE              ,
        canceltransflag CHAR(1)      ,
        cancelflag CHAR(1)           ,
        clsno VARCHAR(32)            ,
        seqno INT                ,
        rnwseqno INT                  ,
        bal DECIMAL(16,2)            ,
        cardno VARCHAR(19)           ,
        oppclsno VARCHAR(32)         ,
        rate DECIMAL(10,6)           ,
        intamt DECIMAL(16,2)         ,
        memocode VARCHAR(4)          ,
        memo VARCHAR(40)             ,
        memo1 VARCHAR(108)           ,
        modifytime  TIMESTAMP        ,
        CONSTRAINT counter_idx UNIQUE (trandate, serseqno, ctxnseq)
    );
    
COMMENT on table glssubtranslog is '实时柜面还款' ;
COMMENT ON    glssubtranslog
    (
        trandate          is     '交易日期',
        serseqno          is  '主机流水号',
        ctxnseq           is  '子交易流水号',
        trancode          is   '交易代码',
        subtrancode       is     '子交易代码',
        submark           is    '子交易标识',
        brc                 is    '交易机构',
        openbrc           is   '委托机构',
        profitbrc         is   '核算机构',
        teller              is    '交易柜员',
        rteller           is   '复核柜员',
        ateller           is   '授权柜员',
        ccy             is       '币种',
        tranamt           is     '发生额',
        cashtranflag     is   '现转标志/钞汇标志 1-现金/现钞 2-转帐/现汇',
        cdflag            is      '借贷标志 :D-借 C-贷',
        subctrlcode       is    '科目控制字',
        acctno            is      '客户帐号',
        subacctno         is  '款项代码',
        subsys            is  '子系统',
        name             is   '户名',
        customerid        is   '客户号',
        customtype        is   '客户类别  1-个人2-对公3-金融',
        acctno1           is   '对方帐号',
        subacctno1        is   '对方款项代码',
        transource       is   '交易来源',
        frntno            is   '前置机编号',
        termcode          is     '终端代码',
        termseq           is    '终端流水号',
        termdate          is    '终端交易日期',
        termtime          is     '终端交易时间',
        acctype           is  '帐别',
        subrectype        is  '帐务类型 0-表外  1-表内',
        effectdate        is         '生效日期',
        "TIME"              is  '机器时间',
        voukind           is    '' ,
        precharcode       is   '冠字代码',
        beginvouno        is  '起始凭证号',
        endvouno          is  '终止凭证号',
        billdate          is  '出票日期',
        cancelstan        is  '冲正错帐流水号',
        postflag          is  '分录标志 0-非分录流水 1-分录流水',
        cashbox           is  '尾箱号',
        cashitemno        is  '现金项目号',
        trantype          is  '交易类型 0：正常 1：蓝字 2：红字',
        reviewflag        is  '复核状态  0：未复核 1：已复核',
        accmode           is  ' 记帐方式  1-单式记帐 2-复式记帐',
        enlistflag        is  '入明细标志  0.未入明细 1.已入明细',
        subrecmode        is  '入明细方式 0-日间实时 1.单笔  2.汇总',
        enaccflag         is  '入分户标志: 0.未入分户 1.已入分户',
        trankind          is  '交易性质: 第一位：开销户性质 0-预置1-开户2-销户  3-挂失补开4-挂失销户',
        busitype          is  '业务种类',
        fstlogflag        is  '主流水标志',
        cancelctrl      is    '冲销控制 0.不能冲销 1.可以冲销',
        prdcode           is  '产品代码',
        prdtype           is  '产品种类',
        settletype      is    '清算种类',
        feetype           is '',
        statcode          is     '分析代码',
        reserv1           is     '预留字段',
        reserv2           is     '预留字段',
        reserv3           is     ' 预留字段',
        revsubtran        is     '冲正子交易代码',
        strintdate        is  '起息日期',
        canceltransflag   is     '冲销交易标志 0.正常交易 1.冲销交易',
        cancelflag        is     '被冲销标志 0-未被冲销 1-被冲销',
        clsno               is           '销帐编号',
        seqno               is   '序号',
        rnwseqno          is         '续存号',
        bal                 is   '帐户余额',
        cardno            is         '卡号',
        oppclsno          is         '对方销帐编号',
        rate                is       '利率',
        intamt              is       '利息金额',
        memocode          is         '摘要码',
        memo                is      '备注',
        memo1                is     '备用',
        modifytime            is      'db2的创建时间'     -- 多的字段
    );
    
    

    