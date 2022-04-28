#!/bin/bash
set -e

psql -v ON_ERROR_STOP=1 --username "$POSTGRES_USER" --dbname "$POSTGRES_DB" <<-EOSQL
    CREATE TABLE public.account_money_transfer (
        id integer NOT NULL,
        from_acc_number text NOT NULL,
        to_acc_number text NOT NULL,
        amount numeric(12,2) NOT NULL,
        date timestamp without time zone NOT NULL,
        status integer NOT NULL,
        description character varying(1000),
        category integer NOT NULL,
        reserved character varying(20)
    );


    ALTER TABLE public.account_money_transfer OWNER TO postgres;

    --
    -- Name: account_money_transfer_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
    --

    CREATE SEQUENCE public.account_money_transfer_id_seq
        AS integer
        START WITH 1
        INCREMENT BY 1
        NO MINVALUE
        NO MAXVALUE
        CACHE 1;


    ALTER TABLE public.account_money_transfer_id_seq OWNER TO postgres;

    --
    -- Name: account_money_transfer_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
    --

    ALTER SEQUENCE public.account_money_transfer_id_seq OWNED BY public.account_money_transfer.id;


    --
    -- Name: account_money_transfer id; Type: DEFAULT; Schema: public; Owner: postgres
    --

    ALTER TABLE ONLY public.account_money_transfer ALTER COLUMN id SET DEFAULT nextval('public.account_money_transfer_id_seq'::regclass);


    --
    -- Name: account_money_transfer account_money_transfer_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
    --

    ALTER TABLE ONLY public.account_money_transfer
        ADD CONSTRAINT account_money_transfer_pkey PRIMARY KEY (id);


    --
    -- PostgreSQL database dump complete
    --
EOSQL