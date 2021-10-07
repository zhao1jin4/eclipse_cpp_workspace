select   
MSGID            as '报文标识号',
INSTGPTY         as '发起参与机构',
TXID             as '交易标识号',
CHCKDT           as '对账日期',
STTLMAMT         as '结算金额',
DBTRACCTNAME     as '付款人户名',
DBTRACCTNO       as '付款人账号',
DBTRPRTRY        as '付款人账户类型',
DBTRISSR         as '付款人开户行名称',
DBTRCTRYSUBDVSN  as '付款人开户行所属城市代码',
DBTRBRNCHID      as '付款人开户行所属网银系统行号',
CDTRACCTNAME     as '收款人户名',
CDTRACCTNO       as '收款人账号',
CREDPRTRY        as '收款人账号类型',
CDTRISSR         as '收款人开户行名称',
CTRYSUBDVSN      as '收款人开户行所属城市代码',
CDTRBRNCHID      as '收款人开户行所属网银系统行号',
BUSIID           as '平台流水号'
from  tbl_bcomecred 
;


