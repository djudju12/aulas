import 'package:flutter/material.dart';

class AnswerButton extends StatelessWidget {
  final String data;
  final void Function() callback;
  const AnswerButton(this.data, this.callback, {super.key});

  @override
  Widget build(context) {
    return ElevatedButton(
      onPressed: callback,
      style: ElevatedButton.styleFrom(
        padding: const EdgeInsets.symmetric(
          horizontal: 40,
          vertical: 10,
        ),
        backgroundColor: const Color.fromARGB(255, 112, 31, 173),
        foregroundColor: Colors.white,
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(40),
        ),
      ),
      child: Text(
        data,
        textAlign: TextAlign.center,
      ),
    );
  }
}
