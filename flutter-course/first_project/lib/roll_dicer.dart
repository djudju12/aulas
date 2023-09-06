import 'dart:io';
import 'dart:math';

import 'package:flutter/material.dart';

class RollDicer extends StatefulWidget {
  const RollDicer({super.key});

  @override
  State<RollDicer> createState() {
    return _DiceRollerState();
  }
}

class _DiceRollerState extends State<RollDicer> {
  String path = "assets/dice-images/dice-4.png";
  final random = Random();

  void rollDice() {
    int i = random.nextInt(6) + 1;
    setState(() {
      path = "assets/dice-images/dice-$i.png";
    });
  }

  @override
  Widget build(context) {
    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        Image.asset(
          path,
          width: 200,
        ),
        const SizedBox(
          height: 20,
        ),
        TextButton(
          onPressed: rollDice,
          style: TextButton.styleFrom(
            foregroundColor: Colors.white,
            textStyle: const TextStyle(fontSize: 28),
            // padding: const EdgeInsets.only(
            //   top: 20,
            // ),
          ),
          child: const Text("Roll Dice"),
        )
      ],
    );
  }
}
