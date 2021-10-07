
 select ifnull(e.trandate,'') as 'ext主机日期',ifnull(e.frntdate,'') as 'ext前置日期',d.batchno as 'def批次号',ifnull(e.bmshm,'') as 'ext对手行转账户名' ,ifnull(e.bmszh,'') as 'ext对手行转账账号' ,  d.amt as '交易金额' ,
 ifnull(e.cnapsbankno ,'')as 'ext对手行行号',ifnull(e.accptbrcname1,'') as 'ext对手行名称',ifnull(e.channel,'') as 'ext交易来源',
d.trandate as 'def交易日期',d.sysdate as 'def系统日期',d.dbrc as 'def借方机构',d.dbaccount as 'def借方账号',d.cbrc as 'def贷方机构',d.craccount as 'def贷方账号',d.channelid as 'def交易渠道',d.description as 'def交易说明', 
d.keyword as  'def顺序号', d.seqno as  'def运行顺序' , d.serseqno as 'def主机流水号' ,            
d.errmsg as 'def错误说明 ',d.memo1 as 'def保留位1 ',d.memo2 as 'def保留位2 ',d.amt1 as 'def保留位3',d.amt2 as 'def保留位4',
ifnull(e.memo1,'') as 'ext备注字段1',
ifnull(e.memo2,'') as 'ext备注字段2',
ifnull(e.memo3,'') as 'ext备注字段3',
ifnull(e.memo4,'') as 'ext备注字段4',
ifnull(e.memo5,'') as 'ext备注字段1'
from  repay_batch_pubtrandef d left join  repay_batch_pubtranext e
on  d.batchno=e.batchno and
d.memocode=e.memocode and
d.keyword =e.keyword   
;


