import java.util.ArrayList;
import java.util.Scanner;

class Transaction {
    private String type;
    private double amount;

    public Transaction(String type, double amount) {
        this.type = type;
        this.amount = amount;
    }

    public String getType() {
        return type;
    }

    public double getAmount() {
        return amount;
    }
}

class Account {
    private String userId;
    private String userPin;
    private double balance;
    private ArrayList<Transaction> transactionHistory;

    public Account(String userId, String userPin) {
        this.userId = userId;
        this.userPin = userPin;
        this.balance = 0.0;
        this.transactionHistory = new ArrayList<>();
    }

    public void deposit(double amount) {
        balance += amount;
        transactionHistory.add(new Transaction("Deposit", amount));
        System.out.println("Deposit successful. Current balance: " + balance);
    }

    public void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactionHistory.add(new Transaction("Withdrawal", amount));
            System.out.println("Withdrawal successful. Current balance: " + balance);
        } else {
            System.out.println("Insufficient funds. Withdrawal failed.");
        }
    }

    public void transfer(Account recipient, double amount) {
        if (amount <= balance) {
            balance -= amount;
            recipient.deposit(amount);
            transactionHistory.add(new Transaction("Transfer to " + recipient.getUserId(), amount));
            System.out.println("Transfer successful. Current balance: " + balance);
        } else {
            System.out.println("Insufficient funds. Transfer failed.");
        }
    }

    public void displayTransactionHistory() {
        System.out.println("Transaction History:");
        for (Transaction transaction : transactionHistory) {
            System.out.println(transaction.getType() + ": " + transaction.getAmount());
        }
    }

    public String getUserId() {
        return userId;
    }

    public String getUserPin() {
        return userPin;
    }

    public double getBalance() {
        return balance;
    }
}

class ATM {
    private Account currentAccount;

    public void start() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter account no: ");
        String userId = scanner.nextLine();
        System.out.print("Enter user PIN: ");
        String userPin = scanner.nextLine();

        // In a real-world scenario, you would authenticate the user based on userId and userPin.
        // For simplicity, this example assumes the user is authenticated.

        currentAccount = new Account(userId, userPin);
        showMenu(scanner);
    }

    private void showMenu(Scanner scanner) {
        while (true) {
            System.out.println("\nATM Menu:");
            System.out.println("1. View Balance");
            System.out.println("2. Deposit Money");
            System.out.println("3. Withdraw Money");
            System.out.println("4. Transfer Money");
            System.out.println("5. View Transaction History");
            System.out.println("6. Quit");

            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume the newline character

            switch (choice) {
                case 1:
                    System.out.println("Current Balance: " + currentAccount.getBalance());
                    break;
                case 2:
                    System.out.print("Enter deposit amount: ");
                    double depositAmount = scanner.nextDouble();
                    currentAccount.deposit(depositAmount);
                    break;
                case 3:
                    System.out.print("Enter withdrawal amount: ");
                    double withdrawalAmount = scanner.nextDouble();
                    currentAccount.withdraw(withdrawalAmount);
                    break;
                case 4:
                    System.out.print("Enter recipient's user ID: ");
                    String recipientUserId = scanner.next();
                    Account recipient = new Account(recipientUserId, "");
                    System.out.print("Enter transfer amount: ");
                    double transferAmount = scanner.nextDouble();
                    currentAccount.transfer(recipient, transferAmount);
                    break;
                case 5:
                    currentAccount.displayTransactionHistory();
                    break;
                case 6:
                    System.out.println("Exiting ATM. Thank you");
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please enter a number between 1 and 6.");
            }
        }
    }
}

public class atmmachine {
    public static void main(String[] args) {
        ATM atm = new ATM();
        atm.start();
    }
}
