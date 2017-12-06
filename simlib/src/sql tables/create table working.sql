CREATE SEQUENCE rows10000000_seq;
CREATE TABLE rows10000000(
   seq       DECIMAL NOT NULL PRIMARY KEY DEFAULT nextval('rows10000000_seq')
  ,first     VARCHAR(20) NOT NULL
  ,last      VARCHAR(20) NOT NULL
  ,age       INTEGER  NOT NULL
  ,street    VARCHAR(30) NOT NULL
  ,city      VARCHAR(15) NOT NULL
  ,state     VARCHAR(5) NOT NULL
  ,zip       DECIMAL  NOT NULL
  ,dollar    VARCHAR(15) NOT NULL
  ,pick      VARCHAR(8) NOT NULL
  ,date      DATE  NOT NULL
  ,email     VARCHAR(30) NOT NULL
  ,digid     DECIMAL  NOT NULL
  ,latitude  NUMERIC(9,5) NOT NULL
  ,longitude NUMERIC(9,5) NOT NULL
  ,pick2     VARCHAR(8) NOT NULL
  ,string    VARCHAR(25) NOT NULL
  ,domain    VARCHAR(20) NOT NULL
  ,float     NUMERIC(18,4) NOT NULL
  ,ccnumber  DECIMAL  NOT NULL
  ,bool      VARCHAR(5) NOT NULL
  ,yn        VARCHAR(1) NOT NULL
);
ALTER SEQUENCE rows10000000_seq OWNED BY rows10000000.seq;