public class CreditAccount implements CreditAccountInterface {
    
    // dichiarare i campi di classe e di oggetto
    private int limit;
    private static int limitLowerBound=1;
    private static int limitUpperBound=2000;
    private int balance;
    private PersonInterface owner;
    //@ invariant limitLowerBound <= limit && limit <= limitUpperBound && balance >= limit && owner != null
	
    // definire i seguenti metodi private di validazione
    
    // PersonInterface requireNonNull(PersonInterface p)
    private static PersonInterface requireNonNull(PersonInterface p){
        if (p==null) throw new IllegalArgumentException("Owner can not be null\n");
        return p;
    }
    // int requirePositive(int amount)
    private static int requirePositive(int amount){
        if (amount<0) throw new IllegalArgumentException("amount can not be negative\n");
        return amount;
    }
    // int requireBalanceGeqLimit(int balance, int limit)
    private static int requireBalanceGeqLimit(int balance, int limit){
        if (balance<limit) throw new IllegalArgumentException("balance can not be lower than limit\n");
        return balance;
    }
    // int requireLimitInBounds(int limit)
    private static int requireLimitInBounds(int limit) {
        if (limit<limitLowerBound || limit>limitUpperBound) 
            throw new IllegalArgumentException("limit invalid\n");
        return limit;
    }

    // definire il costruttore  CreditAccount(int limit, int balance, PersonInterface owner) 
    public CreditAccount(int limit, int balance, PersonInterface owner){
        this.owner=requireNonNull(owner);
        this.limit=requireLimitInBounds(limit);
        this.balance=requireBalanceGeqLimit(balance,this.limit);
    } 
    // definire i seguenti metodi factory
    
    // CreditAccountInterface newOfLimitBalanceOwner(int limit, int balance, PersonInterface owner)
    public static CreditAccountInterface newOfLimitBalanceOwner(int limit, int balance, PersonInterface owner)  {
        return new CreditAccount(limit,balance,owner);
    }
    // CreditAccountInterface newOfBalanceOwner(int balance, PersonInterface owner)
    public static CreditAccountInterface newOfBalanceOwner(int balance, PersonInterface owner)  {
        return new CreditAccount(limitUpperBound,balance,owner);
    }   
    // definire i metodi dell'interfaccia CreditAccountInterface
    public int deposit(int amount){
        this.balance+=requirePositive(amount);
        return this.balance;
    }

	public int withdraw(int amount){
        requirePositive(amount);
        if (this.balance-amount<limit) throw new IllegalArgumentException("You are surpassing the limit\n");
        this.balance-=amount;
        return this.balance;
    }

	public void setLimit(int limit){
        this.limit=requireLimitInBounds(limit);
    }
    public int getBalance(){
        return this.balance;
    }

	public int getLimit(){
        return this.limit;
    }

	public PersonInterface getOwner(){
        return this.owner;
    }
    // definire i metodi getter che non fanno parte dell'interfaccia
    public static int getLimitUpperBound(){
        return limitUpperBound;
    }
    public static int getLimitLowerBound(){
        return limitLowerBound;
    }
}
