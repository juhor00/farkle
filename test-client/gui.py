import tkinter as tk
from tkinter import ttk
from client import Client
import threading
import sys


ROWLEN = 3
COLSPAN = 3


def new_thread(target, daemon=True, args=()):
    thread = threading.Thread(target=target, args=args, daemon=daemon)
    thread.start()


class Gui(tk.Tk):
    def __init__(self, testing: bool):
        super().__init__()
        self.resizable(False, False)

        self.client = Client(self)
        self.widgets = []
        self.title("Farkle commands")
        self.protocol("WM_DELETE_WINDOW", self.__del__)

        self.text_ = tk.Text(self, height=5, width=52, state="disable")
        self.input_ = tk.Label(self)
        self.commands_ = ttk.Combobox(self, state="readonly",
                                      values=["SHOW", "BUST", "TURN", "OVER", "ROUND", "TOTAL", "SAVE", "HOLD", "CLICK"])
        self.commands_.current(0)
        self.dice_ = DiceSelection(self, [1, 2, 3, 4, 5, 6])
        self.player_ = PlayerSelection(self, {"Player": 0, "Opponent": 1})

        # Output
        tk.Label(self, text="Output").grid(columnspan=COLSPAN)
        self.text_.grid(columnspan=COLSPAN)

        # Input
        tk.Label(self, text="Input").grid(columnspan=COLSPAN)
        self.input_.grid(columnspan=COLSPAN)
        tk.Label(self, text="Command").grid(row=4, column=0)
        tk.Label(self, text="Dice").grid(row=4, column=1)
        tk.Label(self, text="Player").grid(row=4, column=2)
        self.commands_.grid(row=5, column=0)
        self.dice_.grid(row=5, column=1)
        self.player_.grid(row=5, column=2)

        # Send
        tk.Button(self, text="Send", command=lambda: self.send_event(None)).grid(columnspan=COLSPAN)

        # Close
        tk.Button(self, text="Close", command=self.__del__).grid(columnspan=COLSPAN)

        # Binds
        self.bind('<Return>', self.send_event)
        self.commands_.bind("<<ComboboxSelected>>", self.generate)
        self.generate()

        self.after(0, new_thread(target=self.client.receive))
        if testing:
            self.client.send(bytes("TEST", encoding="UTF-8"))
        else:
            self.client.send(bytes("JOIN", encoding="UTF-8"))

    def __del__(self):
        print("GUI del")
        self.client.disconnect()
        self.destroy()

    def send_event(self, _):
        msg = self.input_["text"]
        self.client.send(bytes(msg, encoding="UTF-8"))

    def receive_event(self, msg):
        self.text_.config(state="normal")
        self.text_.insert('end', msg+"\n")
        self.text_.see('end')
        self.text_.config(state="disable")

    def generate(self, *args):
        command = self.commands_.get()

        commands = {
            "SHOW": self.dice_,
            "BUST": self.player_,
            "TURN": self.player_,
            "OVER": None,
            "ROUND": self.player_,
            "TOTAL": self.player_,
            "SAVE": self.dice_,
            "HOLD": self.dice_,
            "CLICK": self.dice_,
            }
        widget = commands[command]
        if widget:
            if type(widget) == PlayerSelection:
                if command == "ROUND" or command == "TOTAL":
                    params = widget.get_score()
                else:
                    params = widget.get_player()
            elif type(widget) == DiceSelection:
                if command == "SHOW":
                    params = widget.get_values()
                else:
                    params = widget.get_dice()
            else:
                params = []

            self.input_.config(text=command + " " + " ".join(params))
        else:
            self.input_.config(text=command)


class DiceSelection(tk.Frame):

    def __init__(self, master, values: list):
        super().__init__(master)
        self.dice_selection = []
        self.dice_values = []
        for i, val in enumerate(values):
            selection = tk.IntVar()

            # Selection
            tk.Checkbutton(self, text=val, variable=selection, onvalue=val, offvalue=0, command=self.master.generate)\
                .grid(row=int(i / ROWLEN), column=2 * (i % ROWLEN))

            # Value
            value = ttk.Combobox(self, values=[1, 2, 3, 4, 5, 6], state="readonly", width=2)
            value.current(0)
            value.bind("<<ComboboxSelected>>", self.master.generate)

            self.dice_values.append(value)
            self.dice_selection.append(selection)

            value.grid(row=int(i / ROWLEN), column=2*(i % ROWLEN) + 1)

    def get_dice(self):
        dice = []
        for v in self.dice_selection:
            if v.get() != 0:
                dice.append(str(v.get()))
        return dice

    def get_values(self):
        dice = []
        for die, value in zip(self.dice_selection, self.dice_values):
            if die.get() == 0:
                continue
            else:
                dice.append(f"{die.get()}:{value.get()}")
        return dice

    def disable(self):
        for w in self.winfo_children():
            w.config(state="disable")

    def enable(self):
        for w in self.winfo_children():
            w.config(state="enable")


class PlayerSelection(tk.Frame):

    def __init__(self, master, values: dict):
        super().__init__(master)

        self.var = tk.IntVar()
        self.scores = []

        for i, key in enumerate(values):
            tk.Radiobutton(self, text=key, variable=self.var, value=values[key], command=self.master.generate)\
                .grid(row=i % 2, column=0, sticky="w")
            sv = tk.StringVar(master=self)
            score = tk.Entry(self, width=8, textvariable=sv)
            score.insert(0, '0')
            score.grid(row=i % 2, column=1, sticky="w")
            sv.trace("w", lambda name, mode, index, var=sv: self.master.generate())
            self.scores.append(sv)

    def get_player(self):
        return [str(self.var.get())]

    def get_score(self):
        player = int(self.get_player()[0])
        score = self.scores[player]
        if self.is_score(score.get()):
            return [f"{player}:{score.get()}"]
        else:
            return [f"{player}:0"]

    def disable(self):
        for w in self.winfo_children():
            w.config(state="disable")

    def enable(self):
        for w in self.winfo_children():
            w.config(state="enable")

    @staticmethod
    def is_score(value):
        try:
            int(value)
            return True
        except ValueError:
            return False


if __name__ == '__main__':
    args = sys.argv[1:]
    print(args)
    try:
        args = list(map(int, args))
        if len(args) == 0:
            testing = True
        else:
            testing = bool(args[0])
    except TypeError:
        print("Type error")
        testing = True

    print(testing)
    gui = Gui(testing)
    gui.mainloop()
