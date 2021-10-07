select    
	trandate     as '交易日期    ',
	serseqno     as '主机流水号   ',
	ctxnseq      as '子交易流水号 ',
	tranamt      as '发生额         ',
	cdflag       as '借贷标志    ',
	acctno       as '客户帐号    ',
	name         as '户名      ',
	customerid   as '客户号         ',
	customtype   as '客户类别     ',
	acctno1      as '对方帐号    ',
	subacctno1   as '对方款项代码 ',
	termdate     as '终端交易日期 ',
	termtime     as '终端交易时间 ',
	bal          as '帐户余额    ',
	cardno       as '卡号  ',
	intamt       as '利息金额 ',
	memocode     as '摘要码     ',
	memo         as '备注  ',
	memo1        as '备用  '
from  counter_realtime_tran 
;


